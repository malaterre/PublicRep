for i in $(seq 9 16); do maxval=$(echo "2^$i-1" | bc); echo $maxval;  pfmtopam -maxval=$maxval out.pfm > out.pfm.$maxval.pgm ; done
