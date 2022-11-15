#include <cstdlib>
#include <iostream>
#include <string>
#include "Problem.h"

int main(int argc, char* argv[]) {
    // 1 - input
    // 2 - INITIAL_TEMP
    // 3 - MIN_TEMP
    // 4 - COOLING_RATE
    // 5 - MAX_NEIGHBORS
    if (argc == 1) {
	fprintf(stderr, "Please provide a file as an argument");
	exit(1);
    }

    const int INITIAL_TEMP = 600000;
    const int MIN_TEMP = 5;
    const float COOLING_RATE = 0.97;
    const int MAX_NEIGHBORS = 40;
    //    const int INITIAL_TEMP = std::stoi(argv[2]);
    //    const int MIN_TEMP = std::stoi(argv[3]);
    //    const float COOLING_RATE = std::stof(argv[4]);
    //    const int MAX_NEIGHBORS = std::stoi(argv[5]);

    //    std::cout<<"INITIAL_TEMP = "<<INITIAL_TEMP<<"\n";
    //    std::cout<<"MIN_TEMP = "<<MIN_TEMP<<"\n";
    //    std::cout<<"COOLING_RATE = "<<COOLING_RATE<<"\n";
    //    std::cout<<"MAX_NEIGHBORS = "<<MAX_NEIGHBORS<<"\n";
    
    srand(time(0));
    Problem problem;
    problem.readFrom(argv[1]);
    problem.solveAnnealing(INITIAL_TEMP, MIN_TEMP, COOLING_RATE, MAX_NEIGHBORS);
    //problem.print();
    problem.computeSolutionValue();
    problem.save(argc, argv);
    return 0;
}
