#!/bin/sh -e

for i in $(seq 0 255); do
  value=$(printf "%02x%02x%02x\n" $i $i $i)
  convert -colorspace gray -size 512x512 -depth 8 xc:#$value test.pgm
  # quality:100 imply quant tables are 1's only
  cjpeg -grayscale -optimize -quality 100 -outfile test.jpg test.pgm
  djpeg -outfile test.jpg.pgm test.jpg
  cmp test.jpg.pgm test.pgm
done
