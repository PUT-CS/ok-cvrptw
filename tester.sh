#!/bin/sh
mkdir solutions
for f in data/*; do
    ./cvrptw $f > solutions/${f:4:5}_"solution.txt"
    echo "Solved $f"
done
