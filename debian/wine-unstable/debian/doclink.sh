#!/bin/bash
SRC="$1"
sed -n 's,^Package: ,,p' debian/control |
while read PKG; do
  if [ "$SRC" != "$PKG" -a -d debian/$PKG ]; then
    # create symlink
    install -d debian/$PKG/usr/share/doc
    pushd debian/$PKG/usr/share/doc > /dev/null
    [ ! -d $PKG ] || rmdir $PKG
    [ -d $PKG ] || mkdir $SRC
    ln -s $SRC $PKG
    popd > /dev/null
    # since dpkg won't itself change a directory into a symlink on upgrade,
    # emit maintainer script fragment to ensure proper upgrade
    echo "if [ \"\$1\" = \"upgrade\" -a -d /usr/share/doc/$PKG ]; then rm -rf /usr/share/doc/$PKG; fi" >> debian/$PKG.preinst.debhelper
  fi
done
# return success
true
