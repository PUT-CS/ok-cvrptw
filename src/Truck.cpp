#include "Truck.h"
#include "Depot.h"
#include "functions.h"
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

std::vector<Depot> Truck::solveAnnealing(Depot &start, int INITIAL_TEMP, int MIN_TEMP, float COOLING_RATE, int MAX_NEIGHBORS ) {
    // we have to create a feasible route through assigned depots
    if (this->assignment.empty()) {
        return this->assignment;
    }
    
    float temperature = INITIAL_TEMP;

    // generate a random, feasible solution
    std::vector<Depot> initial_solution = get_initial_solution(this->assignment, this->capacity, start);

    // check if the initial solution was found within the specified iteration limit
    if (initial_solution.size() == 1 && initial_solution[0].num == -1) {
        // the solution wasn't found
        Depot d;
        d.num = -1;
        std::vector<Depot> v{d};
        return v;
    }
    
    std::vector<Depot> current = initial_solution;
    std::vector<Depot> best = current;

    while (temperature > MIN_TEMP) {
        int i = 0;
        // przeszukaj MAX_NEIGHBORS sąsiadów obecnego rozwiązania
        while (i < MAX_NEIGHBORS) {
            auto neighbor =
                get_neighboring_solution(current, start, this->capacity);
            
            if (objective_function(neighbor) <= objective_function(current) ||
                roll() < choose_worse_solution(temperature, current, neighbor)) {
                // accept the neighbor
                current = neighbor;
                
                if (objective_function(current) <= objective_function(best))
                    best = current;
            }
            i++;
        }
        // oblicz t_{i+1}
        temperature *= COOLING_RATE;
    }
    return best;
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

Truck::Truck(int c) {
    this->capacity = c;
    this->assignment.reserve(1001);
}

Truck::~Truck() {}

