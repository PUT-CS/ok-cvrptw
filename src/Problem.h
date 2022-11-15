#ifndef PROBLEM_H
#define PROBLEM_H
#include <iostream>
#include <random>
#include <vector>
#include "Truck.h"
#include "Depot.h"
/*
      std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(25, 63); // define the range

 */
class Problem {
public:
    int num_of_trucks, truck_capacity;
    double min_angle, max_angle;
    std::vector<Depot> depots;
    std::vector<Truck> trucks;
    Depot start_depot;
    std::vector<std::vector<Depot>> solution;
    std::vector<std::vector<double>> distances;
    double solution_sum = 0;
    int routes = 0;
    bool bad_assignment = true;
    void computeDistances();
    void readFrom(std::string filename);
    void assignDepotsToTrucks(int truck_num);
    void preliminaryCheck();
    void print();
    void printDistances();
    void solveAnnealing(int INITIAL_TEMP, int MIN_TEMP, float COOLING_RATE, int MAX_NEIGHBORS);
    void save(int argc, char* argv[]);
    void printSolution();
    void computeSolutionValue();
    void saveSolutionToFile(char* name);
};

#endif
