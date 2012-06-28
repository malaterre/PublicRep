#!/bin/bash
SUFFIX="$1"
shift
ARCHS="$@"

for ext in deps recs; do
  for dep in debian/*.${ext}; do
    package="$(basename "$dep" .${ext})"
    path="debian/$package$SUFFIX"
    deplist=$(sed 's,^,-l,' $dep)
  #  echo $path: $deplist
    for arch in $ARCHS; do
      gcc -m$arch -Wl,--noinhibit-exec -o "$path/extra${ext}$arch" debian/extradep.c $deplist
    done
  done
done

# return success
true
