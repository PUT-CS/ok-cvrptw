#!/bin/sh
mkdir quality_tests 2> /dev/null
touch quality_tests/1_100.log
for i in {1..100}
do
    echo "Quality testing with i = $i"
    echo "$i $(./cvrptw data/rc21010.txt $i)" >> performance_tests/1_100.log
done 
