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
    int randIntInRangeInclusive(int min, int max);
    void readFrom(std::string filename);
    void assignDepotsToTrucks(int truck_num);
    void print();
    void solveAnnealing();
};

#endif
