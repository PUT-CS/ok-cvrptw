#include "Truck.h"
#include "Depot.h"
#include "functions.h"
#include <cmath>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

std::vector<Depot> Truck::solveAnnealing(Depot &start) {
    // we have to create a feasible route through assigned depots

    if (this->assignment.empty()) {
        return this->assignment;
    }
    
    const int MAX_ITER = 50;
    const int INITIAL_TEMP = 30000;
    const int MIN_TEMP = 5;
    const float COOLING_CONSTANT = 0.99;
    float temperature = INITIAL_TEMP;
    int i = 0;

    std::vector<Depot> initial_solution = get_initial_solution(this->assignment, this->capacity, start);

    // check if the initial solution was found within the specified iteration limit
    if (initial_solution.size() == 1 && initial_solution[0].num == -1) {
        // the solution wasn't found
        Depot d;
        d.num = -1;
        std::vector<Depot> v{d};
        return v;
    }
    std::vector<Depot> current_solution(initial_solution);
    
    return current_solution;
    
    std::vector<Depot> best_solution(current_solution);

    while (temperature > MIN_TEMP) {
        while (i < MAX_ITER) {
            std::vector<Depot> neighbor_solution = get_neighboring_solution(current_solution, start);
            if (objective_function(neighbor_solution) <= objective_function(current_solution) ||
                roll() < choose_worse_solution(temperature, current_solution, neighbor_solution)) {
                // accept the neighbor
                current_solution.assign(neighbor_solution.begin(), neighbor_solution.end());
                
                if (objective_function(current_solution) <= objective_function(best_solution)) {
                    best_solution.assign(current_solution.begin(), current_solution.end());
                }
            }
            i++;
        }
        temperature *= COOLING_CONSTANT;
    }
    
    return best_solution;
}

void Truck::print() {
    std::cout<<"Amount left: "<<this->capacity<<std::endl;
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

Truck::Truck(int c) { this->capacity = c; }

Truck::~Truck() {}

