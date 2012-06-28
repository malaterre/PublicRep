#!/bin/bash
SUFFIX="$1"

for ext in deps recs; do
  for dep in debian/*.${ext}; do
    package="$(basename "$dep" .${ext})"
    path="debian/$package$SUFFIX"
  #  echo $path
    rm -f "$path/extra${ext}32" "$path/extra${ext}64"
  done
done

# return success
true
