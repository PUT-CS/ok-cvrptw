#include <iostream>
#include <iomanip>
class Depot {
public:
    int num, x, y, demand, ready_time, end_time, service_duration;
    double dist, angle;
    void print(); 
    Depot() {}
    ~Depot() {}
};
