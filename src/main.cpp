#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include "Problem.h"

int main(int argc, char* argv[]) {
    // 1 - input file
    // 2 - INITIAL_TEMP
    // 3 - MIN_TEMP
    // 4 - COOLING_RATE
    // 5 - MAX_NEIGHBORS
    if (argc == 1) {
	fprintf(stderr, "Please provide a file as an argument");
	exit(1);
    }

    if (std::string(argv[1]) == "--help") {
        std::cout<<"Usage:\n";
        std::cout<<"cvrptw FILE [INITIAL_TEMPERATURE] [MINIMAL_TEMPERATURE] [COOLING_RATE] [MAX_NEIGHBORS]\n\n";
        std::cout<<"Finds solutions to the Capacitated Vehicle Routing Problem With Time Windows by using simulated annealing.\n"
            "Outputs '-1' if a valid solution could not be found within time limits\n"
            "Provided input files must be proper Salomon formatted instances\n";
        exit(0);
    }

    // default values
    int INITIAL_TEMP = 600000;
    int MIN_TEMP = 5;
    double COOLING_RATE = 0.97;
    int MAX_NEIGHBORS = 50;
    
    Problem problem;
    
    if (argc == 6) {
        INITIAL_TEMP = std::stoi(argv[2]);
        MIN_TEMP = std::stoi(argv[3]);
        COOLING_RATE = std::stof(argv[4]);
        MAX_NEIGHBORS = std::stoi(argv[5]);
    } else if (argc == 3 && (strcmp("--visualize", argv[2]) || strcmp("-vis", argv[2]))) {
        problem.visualize = true;
    }

    srand(time(0));
    problem.readFrom(argv[1]);
    problem.preliminaryCheck();
    problem.solveAnnealing(INITIAL_TEMP, MIN_TEMP, COOLING_RATE, MAX_NEIGHBORS);
    problem.computeSolutionValue();
    if (problem.visualize)
        problem.visualizeSolution(argv[1]);
    problem.save(argc, argv);

    return 0;
}
