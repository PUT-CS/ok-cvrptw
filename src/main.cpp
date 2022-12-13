#include "Problem.h"
#include "functions.h"
#include <bits/chrono.h>
#include <chrono>
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    auto program_start = std::chrono::high_resolution_clock().now();
    
    if (argc == 1) {
        fprintf(stderr, "Please provide a file as an argument");
        exit(1);
    }

    if (std::string(argv[1]) == "--help") {
        std::cout << "Usage:\n";
        std::cout << "cvrptw FILE [MAX_FREQUENCY] [MAX_TABU_SIZE]\n\n";
        std::cout << "Finds solutions to the Capacitated Vehicle Routing Problem With Time Windows by using the tabu search metaheuristic method.\n"
                     "Outputs '-1' as the number of routes if a valid solution could not be found within set time limits\n"
                     "Provided input files must be proper Salomon formatted instances\n";
        exit(0);
    }

    // default values
    int MAX_FREQUENCY = 1000;
    int MAX_TABU_SIZE = 20;

    Problem problem;

    if (argc == 4) {
        MAX_FREQUENCY = std::stoi(argv[2]);
        MAX_TABU_SIZE = std::stoi(argv[3]);
    } else if (argc == 3 && (std::string(argv[2]) == std::string("--visualize") || std::string(argv[2]) == std::string("-v"))) {
        problem.visualize = true;
    }

    srand(time(0));
    problem.readFrom(argv[1]);
    problem.preliminaryCheck();
    problem.solveTabuSearch(MAX_FREQUENCY, MAX_TABU_SIZE);
    problem.computeSolutionValue();
    if (problem.visualize)
        problem.visualizeSolution(argv[1]);
    problem.save(argc, argv);
    auto program_end = std::chrono::high_resolution_clock().now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(program_end - program_start);
    //std::cout<<duration.count()<<std::endl;

    return 0;
}
