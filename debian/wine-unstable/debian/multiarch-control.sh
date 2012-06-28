#!/bin/bash
MULTIARCH="$1"
WIN64="$2"

if [ "$MULTIARCH" != "y" ]; then
# if not using full multiarch, delete the Multi-Arch fields.
sed -i "/^Multi-Arch: / d" debian/control
else
if [ "$WIN64" != "y" ]; then
# if using full multiarch, but without win64, do not build on amd64
sed -i "/^Architecture: / s/ \(\w\+-\)\?amd64\b//g" debian/control
fi
fi

# return success
true
