#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string>
#include "Problem.h"
#include "functions.h"

int main(int argc, char* argv[]) {

    auto program_start = std::chrono::high_resolution_clock().now();
    
    if (argc == 1) {
        fprintf(stderr, "Please provide a file as an argument");
	exit(1);
    }
    
    if (std::string(argv[1]) == "--help") {
        std::cout<<"Usage:\n";
        std::cout<<"cvrptw FILE [INITIAL_TEMPERATURE] [MINIMAL_TEMPERATURE] [COOLING_RATE] [MAX_NEIGHBORS]\n\n";
        std::cout<<"Finds solutions to the Capacitated Vehicle Routing Problem With Time Windows by using simulated annealing.\n"
            "Outputs '-1' as the number of routes if a valid solution could not be found within set time limits\n"
            "Provided input files must be proper Salomon formatted instances\n";
        exit(0);
    }

    // number between 1-1000, for performance testing
    int depot_count = std::stoi(argv[2]);
    
    // default values
    int INITIAL_TEMP = 10000;
    int MIN_TEMP = 5;
    double COOLING_RATE = 0.95;
    int MAX_NEIGHBORS = 10;
    
    Problem problem;
    
    srand(time(0));
    problem.readFrom(argv[1], depot_count);
    problem.preliminaryCheck();
    problem.solveAnnealing(INITIAL_TEMP, MIN_TEMP, COOLING_RATE, MAX_NEIGHBORS);
    problem.computeSolutionValue();
    if (problem.visualize)
        problem.visualizeSolution(argv[1]);
    problem.save(argc, argv);

    auto program_end = std::chrono::high_resolution_clock().now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(program_end - program_start);
    std::cout<<duration.count()<<std::endl;
    
    return 0;
}
