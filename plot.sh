#!/bin/bash
cat $1 | awk 'NR>9 {printf("%s %s\n", $2, $3)}' > vis/tmp;
gnuplot -p -e "set nokey; set xlabel 'x'; set ylabel 'y'; plot 'vis/tmp' every ::1 w p pt 7 ps 1,  '< cat vis/tmp | head -n 1' w p lw 5 pt 7 ps 2"
rm -f vis/tmp
