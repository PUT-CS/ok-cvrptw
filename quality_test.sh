#!/bin/sh
mkdir quality_tests
for i in {901..1000}
do
    echo "Doing $i"
    echo "$i $(./cvrptw data/rc21010.txt $i | head -n 1 | awk '{printf("%f %f\n", $2, $3)}')" >> quality_tests/rc21010_901_1000.txt
done

            
