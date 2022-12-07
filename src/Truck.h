#ifndef TRUCK_H
#define TRUCK_H
#include "Depot.h"
#include <vector>

class Truck {
public:
    int capacity;
    std::vector<Depot> assignment;
    std::vector<Depot> route;
    void print();
    std::vector<Depot> solveAnnealing(Depot& start, int INITIAL_TEMP, int MIN_TEMP, float COOLING_RATE, int MAX_NEIGHBORS, double* random_ptr);
    bool isSolutionFeasible(std::vector<Depot> solution);
    Truck(int c);
    ~Truck();
};

#endif
