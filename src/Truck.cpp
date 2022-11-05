#include "Truck.h"
#include <iostream>
#include <vector>

Truck::Truck(int c) { this->amount_left = c; }

Truck::~Truck() {}

void Truck::print() {
    std::cout<<"Amount left: "<<this->amount_left<<std::endl;
    std::cout<<"Assignment: "<<std::endl;
    for (Depot d : this->assignment) {
	std::cout<<d.num<<" ";
    }
    std::cout<<std::endl;
    std::cout<<"Route: "<<std::endl;
    for (Depot d : this->route) {
	std::cout<<d.num<<" ";
    }
}

std::vector<Depot> Truck::solveSubproblem(Depot &start) {
    // we have to create a route through assigned depots
    std::vector<Depot> solution;
    solution.push_back(start);
    return this->assignment;
}
