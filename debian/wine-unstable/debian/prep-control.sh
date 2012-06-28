#!/bin/bash
SUFFIX="$1"

sed -n "
/^[ ]/! {
 x
 s/^\(Source: \|Package: \).*$/&${SUFFIX}/ 
 /^\(Depends\|Recommends\|Suggests\|Replaces\): .*[^,]$/ {
  s/\([\n:,|] \)\([a-z0-9_-]*wine[a-z0-9_-]*\)/\1\2${SUFFIX}/g
  s/wine-doc${SUFFIX}/wine-doc/g
 }
 /^./ p
 x
 /^$/ p
 h
}
/^[ ]/ H
" debian/control.in > debian/control

if [ -n "$SUFFIX" ]; then
sed -i -n "
/^Source: / h
/^Package: / {
 : PKG
 x
 /^Conflicts: /M s/Package: \([^\n]*\)${SUFFIX}\n\(\([^\n]*\n\)*\)Conflicts: \(.*\)$/Package: \1${SUFFIX}\n\2Conflicts: \4, \1/M
 /^Conflicts: /M! s/Package: \([^\n]*\)${SUFFIX}\n\(\([^\n]*\n\)*\)Description: /Package: \1${SUFFIX}\n\2Conflicts: \1\nDescription: /M
 /^./ p
 x
 $ q
 h
}
/^Source: \|^Package: /! H
$ b PKG
" debian/control
fi

# return success
true
