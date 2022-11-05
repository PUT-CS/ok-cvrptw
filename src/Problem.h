#ifndef PROBLEM_H
#define PROBLEM_H
#include <iostream>
#include <vector>
#include "Truck.h"
#include "Depot.h"

class Problem {
public:
    int num_of_trucks, truck_capacity;
    double min_angle, max_angle;
    std::vector<Depot> depots;
    std::vector<Truck> trucks;
    Depot start_depot;
    std::vector<std::vector<Depot>> solution;
    void readFrom(std::string filename);
    void assignDepotsToTrucks();
    void print();
    void solveGreedy();
};

#endif
