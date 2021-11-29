#!/bin/sh

wget -c http://igm.univ-mlv.fr/~incerti/IMAGES/pgm/lena.512.pgm

input1=lena.512.pgm
input2=lena.512.pgm
for step in $(seq 1 20); do
  #echo $step;
  cjpeg -grayscale -optimize -quality 100 -outfile output1_$step.jpg $input1
  djpeg -outfile output1_$step.pgm output1_$step.jpg
  #cmp $input1 output1_$step.pgm
  #diff1=$(compare -metric AE $input1 output1_$step.pgm null: 2>&1)
  diff1=$(compare -metric AE $input1 output1_$step.pgm diff1_$step.png 2>&1)
  echo "$step turbo: $diff1"
  jpeg -q 100 $input2 output2_$step.jpg 2>&1 > /dev/null
  jpeg output2_$step.jpg output2_$step.pgm 2>&1 > /dev/null
  #diff2=$(compare -metric AE $input2 output2_$step.pgm null: 2>&1)
  diff2=$(compare -metric AE $input2 output2_$step.pgm diff2_$step.png 2>&1)
  echo "$step libjpeg: $diff2"
  input1=output1_$step.pgm
  input2=output2_$step.pgm
done
