#!/bin/bash
SUFFIX="$1"

for ext in install links mime config preinst postinst prerm postrm docs manpages lintian-overrides; do
  for inst in debian/*.${ext}-common; do
    package="$(basename "$inst" .${ext}-common)"
    rm -f debian/$package$SUFFIX.${ext}
  done
done

# return success
true
