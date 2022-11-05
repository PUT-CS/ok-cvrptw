#ifndef TRUCK_H
#define TRUCK_H
#include <vector>
#include "Depot.h"

class Truck {
public:
    int amount_left;
    std::vector<Depot> assignment;
    std::vector<Depot> route;
    void print();
    std::vector<Depot> solveSubproblem(Depot &start);
    Truck(int c);
    ~Truck();
};

#endif
