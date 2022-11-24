#!/bin/sh
mkdir performance_tests 2> /dev/null
touch performance_tests/801_1000.log
for i in {801..1000}
do
    echo "Performance testing with i = $i"
    echo "$i $(./cvrptw data/rc21010.txt $i)" >> performance_tests/801_1000.log
done 
