#include <iostream>
#include <vector>
#include "Depot.h"

class Problem {
public:
    int num_of_trucks, truck_capacity;
    std::vector<Depot> depots;
    Depot start_depot;
    void readFrom(std::string filename);
    void print();
};
