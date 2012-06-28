#!/bin/bash
PREFIX="$1"
DIR="$2"
echo "Symlinking in ia32-libs..."
while read LIB NAME; do
  LIBPATH="$PREFIX/$LIB"
  LIBNAME="$DIR/$NAME"
  [ -e "$LIBPATH" ] && [ ! -e "$LIBNAME" ] && ln -s "$LIBPATH" "$LIBNAME"
done < debian/ia32.libs
# return success
true
