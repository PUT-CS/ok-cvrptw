#include <iostream>
#include "Problem.h"

int main(int argc, char* argv[]) {
    if (argc == 1) {
	fprintf(stderr, "Please provide a file as an argument");
	exit(1);
    }
    srand(time(0));
    Problem problem;
    problem.readFrom(argv[1]);
    problem.solveAnnealing();
    //problem.print();
    problem.computeSolutionValue();
    problem.save(argc, argv);
    return 0;
}
