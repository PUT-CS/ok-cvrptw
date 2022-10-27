#!/bin/bash
cat $1 | awk 'NR>9 {printf("%s %s\n", $2, $3)}' >> tmp;
gnuplot -p -e "set nokey; set xlabel 'x'; set ylabel 'y'; plot 'tmp' every ::1 w p lw 2 pt 5 ps 1,  '< cat tmp | head -n 1' w p lw 5 pt 5 ps 2"
rm -f tmp
