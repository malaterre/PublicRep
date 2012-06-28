#!/bin/bash
SUFFIX="$1"
LIBDIRS="$2"

function replace_paths_full
{
  sed "s,/usr/lib,/$1," | \
  sed "s,/$1/wine,&$SUFFIX," | \
  sed "s,/usr/share/wine,&$SUFFIX," | \
  sed "s,usr/share/doc/$package,&$SUFFIX," | \
  ([ "$ext" != "lintian-overrides" ] && cat || sed "s,^$package,&$SUFFIX," )
}

function replace_paths_partial
{
  sed -n "s,/usr/lib,/$1,p" | \
  sed "s,/$1/wine,&$SUFFIX,"
}

function expand_common
{
  replace_paths_full $1 < debian/$package.${ext}-common > debian/$package$SUFFIX.${ext}
  shift
  while [ -n "$1" ]; do
    replace_paths_partial $1 < debian/$package.${ext}-common >> debian/$package$SUFFIX.${ext}
    shift
  done
}

# certain binaries are only compiled on some platforms;
# if they were compiled on the current one, install them
function expand_platform
{
  if [ ! -f debian/$package.${ext}-platform ]; then
    return
  fi
  for bin in $(replace_paths_full $1 < debian/$package.${ext}-platform); do
    [ ! -f $bin ] || echo $bin >> debian/$package$SUFFIX.${ext}
  done
  shift
  while [ -n "$1" ]; do
    for bin in $(replace_paths_partial $1 < debian/$package.${ext}-platform); do
      [ ! -f $bin ] || echo $bin >> debian/$package$SUFFIX.${ext}
    done
    shift
  done
}

function expand_modules
{
  if [ ! -f debian/$package.${ext}-modules ]; then
    return
  fi
  while [ -n "$1" ]; do
    for mod in $(cat debian/$package.${ext}-modules); do
      for bin in debian/tmp/$1/wine$SUFFIX/$mod.so debian/tmp/$1/wine$SUFFIX/$mod debian/tmp/$1/wine$SUFFIX/fakedlls/$mod; do
        [ ! -f $bin ] || echo $bin >> debian/$package$SUFFIX.${ext}
      done
    done
    shift
  done
}

for ext in install links mime config preinst postinst prerm postrm docs manpages lintian-overrides; do
  for inst in debian/*.${ext}-common; do
    if [ -f "$inst" ]; then
      package="$(basename "$inst" .${ext}-common)"
      expand_common $LIBDIRS
      expand_platform $LIBDIRS
      expand_modules $LIBDIRS
    fi
  done
done

# return success
true
