#include "Truck.h"
#include "Depot.h"
#include "functions.h"
#include <cmath>
#include <cstdlib>
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

std::vector<Depot> getNeighboringSolution(std::vector<Depot> input) {
    return input;
}

float choose_worse_solution(float temperature, std::vector<Depot> prev, std::vector<Depot> next) {
    return std::exp((-1 *objective_function(next) - objective_function(prev)) / temperature);
}

float roll() {
    return ((double) rand() / (RAND_MAX)) + 1;
}

std::vector<Depot> Truck::solveAnnealing(Depot &start) {
    // we have to create a route through assigned depots

    const int INITIAL_TEMP = 3000;
    const int MIN_TEMP = 5;
    const float COOLING_CONSTANT = 0.98;

    float temperature = INITIAL_TEMP;

    // CHANGE
    std::vector<Depot> current_solution = this->assignment;
    std::vector<Depot> best_solution(current_solution);

    int i = 0;
    while (temperature > INITIAL_TEMP) {

	std::vector<Depot> neighbor_solution = getNeighboringSolution(current_solution);
	
	if (objective_function(neighbor_solution) < objective_function(current_solution) ||
	    roll() < choose_worse_solution(temperature, current_solution, neighbor_solution)) {
	    current_solution.assign(neighbor_solution.begin(), neighbor_solution.end());
	    // accept the neighbor
	    if (objective_function(current_solution) < objective_function(best_solution)) {
		best_solution.assign(current_solution.begin(), current_solution.end());
	    }
	}
	
	temperature *= COOLING_CONSTANT;
    }
    
    
    return this->assignment;
}
