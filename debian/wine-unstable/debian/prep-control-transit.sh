#!/bin/bash
SUFFIX="$1"
TRANSPREFIX="$2"
TRANSSUFFIX="$3"

sed -n "
/^Source: / {
 s/Source: \(.*\)/Source: \1${SUFFIX}/
 h
}
/^Package: / {
 : PKG
 x
 s/Package: \([^\n]*\)\n\(\([^\n]*\n\)*\)Depends: \(.*\n\([ ].*\n\)*\)/Package: \1${SUFFIX}\n\2Depends: ${TRANSPREFIX}\1${TRANSSUFFIX}\n/M
 s/Pre-Depends: .*\n//M
 s/Conflicts: .*\n//M
 s/Recommends: .*\n//M
 s/Suggests: .*\n//M
 s/Replaces: .*\n//M
 /^./ p
 x
 $ q
 h
}
/^Source: \|^Package: /! H
$ b PKG
" debian/control.in > debian/control

# return success
true
