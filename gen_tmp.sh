#!/bin/bash
cat $1 | awk 'NR>9 {printf("%s %s\n", $2, $3)}' > vis/tmp;
