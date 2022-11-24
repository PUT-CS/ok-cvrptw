#ifndef DEPOT_H
#define DEPOT_H
#include <iostream>
#include <iomanip>
class Depot {
public:
    int num, x, y, demand, ready_time, end_time, service_duration;
    void print(); 
    Depot() {}
    ~Depot() {}
};

#endif
