#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <ostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include "Problem.h"

int main(int argc, char* argv[]) {
    if (argc == 1) {
	fprintf(stderr, "Please provide a file as an argument");
	exit(1);
    }
    Problem problem;
    problem.readFrom(argv[1]);
    problem.solveGreedy();
    return 0;
}
