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

Truck::Truck(int c) { this->capacity = c; }

Truck::~Truck() {}

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

std::vector<Depot> getNeighboringSolution(std::vector<Depot> input, Depot start) {
    return input;
}

float choose_worse_solution(float temperature, std::vector<Depot> prev, std::vector<Depot> next) {
    return std::exp((-1 *objective_function(next) - objective_function(prev)) / temperature);
}

float roll() { return ((double)rand() / (RAND_MAX)); }

bool is_solution_feasible(Depot start, std::vector<Depot> solution, int cargo) {

    using std::cout, std::endl;
    
    if (solution.empty()) {
	std::cout<<"Empty solution passed!"<<std::endl;
	return true;
    }
    double time = 0;

    
    Depot current_depot = start;
    
    // go from the start to the first assigned depot
    //time += dist(start, current_depot);
    // cout<<"Arrived at first assigned depot at "<<time<<endl;
    Depot next_depot;
    //std::cout<<"IN LOOP "<<solution.size()<<std::endl;
    for (unsigned long int i = 0; i<solution.size(); i++) {
	// select the target depot
	next_depot = solution[i];

	// add the travel distance
	time += dist(current_depot, next_depot);
	// go from the current town to the next depot
	current_depot = next_depot;
	
	//	cout<<"at depot "<<current_depot.num<<" on time: "<<time<<endl;

	// the truck came too early so we fast forward the time
	if (time < current_depot.ready_time) {
	    time = current_depot.ready_time;
	    //  cout<<"Came early, waited until "<<time<<endl;
	}

	// the truck came too late
	if (time > current_depot.end_time) {
	    //	    std::cout<<"Failed at truck beign late to depot "<<current_depot.num<<std::endl;
	    //	    cout<<"Depot "<<current_depot.num<<" closed at "<<current_depot.end_time<<" and time is "<<time<<endl;
	    return false;
	}

	// there's not enough cargo to serve the depot
	if (cargo < current_depot.demand) {
	    //   std::cout<<"Failed at not enough cargo at depot "<<current_depot.num<<std::endl;
	    return false;
	}

	// unload the truck
	time += current_depot.service_duration;
	//	cout<<"Finished service at "<<current_depot.num<<" at "<<time<<endl;
	// take the cargo
	cargo -= current_depot.demand;
	
    }
    return true;
}
    
std::vector<Depot> get_initial_solution(std::vector<Depot> assignment, int capacity, Depot start) {
    std::random_device rd;
    std::mt19937 gen(rd());
    
    // the route must finish at the start depot
    std::vector<Depot> v {start};
    v.insert(v.end(), assignment.begin(), assignment.end());
    v.push_back(start);
    //    std::cout<<"Initial truck assignment :"<<std::endl;;
    //    print_depot_vec(v);
    // std::cout<<is_solution_feasible(assignment, capacity)<<std::endl;
    //    exit(0);
    int iter_limit = 100;
    while (!is_solution_feasible(start, v, capacity) && iter_limit --> 0) {
	std::shuffle(v.begin()+1, v.end()-1, gen);
	//print_depot_vec(v);
	//	exit(0);
	//	std::cout<<"HERE"<<std::endl;
    }
    if (iter_limit <= 0) {
	Depot d;
	d.num = -1;
	std::vector<Depot> v{d};
	return v;
    }
    return assignment;
}

std::vector<Depot> Truck::solveAnnealing(Depot &start) {
    // we have to create a route through assigned depots

    //print_depot_vec(this->assignment);

    if (this->assignment.empty()) {
	return this->assignment;
    }
    
    const int MAX_ITER = 50;
    const int INITIAL_TEMP = 30000;
    const int MIN_TEMP = 5;
    const float COOLING_CONSTANT = 0.99;
    float temperature = INITIAL_TEMP;
    int i = 0;

    // CHANGE
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
    //nie moge!
    // 
    //    std::cout<<"Initial solution found!"<<std::endl;
    //    print_depot_vec(current_solution);
    //    std::cout<<std::endl;
    return current_solution;
    std::vector<Depot> best_solution(current_solution);
    //print_depot_vec(current_solution);

    while (temperature > MIN_TEMP) {
	//std::cout<<roll()<<std::endl;
	while (i < MAX_ITER) {
	    std::vector<Depot> neighbor_solution = getNeighboringSolution(current_solution, start);
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
    
    return this->assignment;
}
