#!/bin/sh
mkdir performance_tests 2> /dev/null
range=951_1000
touch performance_tests/$range.log
for i in {951..1000}
do
    echo "Performance testing with i = $i"
    echo "$i $(./cvrptw data/rc21010.txt $i)" >> performance_tests/$range.log
done 
