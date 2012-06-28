#!/bin/bash
SUFFIX="$1"

for dep in debian/*.recs; do
  package="$(basename "$dep" .recs)"
  path="debian/$package$SUFFIX"
  dpkg-shlibdeps -O $path/extradeps* -dRecommends $path/extrarecs* 2>/dev/null |
   grep "shlibs:Recommends" >> debian/$package$SUFFIX.substvars
done

# return success
true
