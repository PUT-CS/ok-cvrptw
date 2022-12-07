#!/bin/sh
mkdir quality_tests
range=976_1000
for i in {976..1000}
do
    echo "Doing $i"
    echo "$i $(./cvrptw data/rc21010.txt $i | head -n 1 | awk '{printf("%f %f\n", $1, $2)}')" >> quality_tests/rc21010_$range.txt
done

            
