#ifndef PROBLEM_H
#define PROBLEM_H
#include <iostream>
#include <random>
#include <vector>
#include "Truck.h"
#include "Depot.h"

class Problem {
public:
    int num_of_trucks, truck_capacity;
    std::vector<Depot> depots;
    std::vector<Truck> trucks;
    Depot start_depot;
    std::vector<std::vector<Depot>> solution;
    std::vector<std::vector<double>> distances;
    double solution_sum = 0;
    double before_annealing = 0;
    int routes = 0;
    bool bad_assignment = true;
    bool visualize = false;
    void computeDistances();
    void readFrom(std::string filename, int depot_count);
    void assignDepotsToTrucks(int truck_num);
    void preliminaryCheck();
    void print();
    void printDistances();
    void solveAnnealing(int INITIAL_TEMP, int MIN_TEMP, float COOLING_RATE, int MAX_NEIGHBORS);
    void save(int argc, char* argv[]);
    void printSolution();
    void computeSolutionValue();
    void saveSolutionToFile(char* name);
    void visualizeSolution(char* filename);
};

#endif
