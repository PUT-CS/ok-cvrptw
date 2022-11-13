#include <algorithm>
#include <bits/chrono.h>
#include <bits/types/time_t.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <memory>
#include <ostream>
#include <random>
#include <vector>
#include <bits/stdc++.h>
#include "Depot.h"
#include "Problem.h"
#include "Truck.h"
#include "functions.h"
#include <chrono>
#define PI 3.141593

void skip(std::ifstream &file, int n) {
    std::string buf;
    for (int i=0; i<n; i++)
	file>>buf;
}

void Problem::computeDistances() {
    for (auto &depot1 : this->depots) {
	std::vector<double> n_row;
	for (auto &depot2 : this->depots) {
	    n_row.push_back(dist(depot1, depot2));
	}
	this->distances.push_back(n_row);
    }
}

void Problem::printDistances() {
    for (long unsigned int i = 0; i<this->distances.size(); i++) {
	for (long unsigned int j=0; j<this->distances[0].size(); j++) {
	    std::cout<<this->distances[i][j]<<" ";
	}
	std::cout<<std::endl;
    }
}

    
int Problem::randIntInRangeInclusive(int min, int max) {
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(min, max); // define the range
    return distr(gen);
}

void Problem::readFrom(std::string filename) {
	std::ifstream input(filename, std::ios_base::in);
	std::string buf;
	skip(input, 4);
	input>>this->num_of_trucks;
	input>>this->truck_capacity;
	skip(input, 12);

	while (!input.eof()) {
	    Depot new_depot;
	    input>>
		new_depot.num>>
		new_depot.x>>
		new_depot.y>>
		new_depot.demand>>
		new_depot.ready_time>>
		new_depot.end_time>>
		new_depot.service_duration;
	    this->depots.push_back(new_depot);
	}
	this->start_depot = this->depots[0];
	//	this->min_angle = 360.0;
	//	this->max_angle = 0.0;
	/*for (auto &depot : this->depots) {
	    depot.dist = dist(this->start_depot.x, this->start_depot.y, depot.x, depot.y);
	    depot.angle = slope_in_deg(this->start_depot.x, this->start_depot.y, depot.x, depot.y);
	    if (depot.angle < this->min_angle) {
		this->min_angle = depot.angle;
	    }
	    if (depot.angle > this->max_angle) {
		this->max_angle = depot.angle;
	    }
	    }*/
	for (int i = 0; i<num_of_trucks; i++) {
	    trucks.push_back(Truck(truck_capacity));
	}
	this->depots.pop_back();
	input.close();
}

void Problem::print() {
	std::cout<<"Truck Number: "
		 <<this->num_of_trucks<<std::endl
		 <<"Truck Capacity: "
		 <<this->truck_capacity<<std::endl;
	for (unsigned long int i=0; i<this->depots.size(); i++) {
	    Depot d = this->depots[i];
	    std::cout
		<<d.num<<'\t'
		<<d.x<<'\t'
		<<d.y<<'\t'
		<<"dist=" <<d.dist<<"\t"
		//<<"angle="<<d.angle<<"\t"
		<<d.demand<<'\t'
		<<d.ready_time<<'\t'
		<<d.end_time<<'\t'
		<<d.service_duration<<'\t'
		<<std::endl;
	}
	std::cout<<"Min, Max Angles: "<< this->min_angle << ", " << this->max_angle<<std::endl;
	for (Truck t : this->trucks) {
	    t.print();
	}
	std::cout<<std::endl<<"Solution: "<<std::endl;
	for (auto &solution_vec : this->solution) {
	    for (auto &depot : solution_vec) {
		std::cout<<depot.num<<" ";
	    }
	    std::cout<<std::endl;
	}
}

/// Randomly assign depots to trucks
void Problem::assignDepotsToTrucks(int truck_num) {

    // deep copy depots
    std::vector<Depot> tmp_depot_vec(this->depots);

    // index of the truck we are currently assigning for
    int current_truck_idx = 0;
    int max_truck_idx = truck_num;

    // clear the assignments in case this function is run multiple times due to bad assignments
    for (auto &truck : this->trucks) {
	truck.assignment.clear();
    }
    
    // while there are still some unassigned depots
    // `-1` since we are leaving the starting depot as is
    while (tmp_depot_vec.size()-1 != 0) {

	int rand_idx = this->randIntInRangeInclusive(1, tmp_depot_vec.size()-1);
	
	// assing the depot, mark it as assigned by removing from tmp_depot_vec
	this->trucks[current_truck_idx].assignment.push_back(tmp_depot_vec[rand_idx]);

	// remove rand_idx from tmp_depot_vec;
	tmp_depot_vec.erase(tmp_depot_vec.begin()+rand_idx);

	//for (auto &de : tmp_depot_vec) {
	//	    std::cout<<de.num<<" ";
	//	}
	//	std::cout<<std::endl;
	
        // set what truck is to be assigned to next
	current_truck_idx = (current_truck_idx+1) % max_truck_idx;
    }
}

void Problem::solveAnnealing() {
    // depot 0 never gets assigned!
    // this->assignDepotsToTrucks(this->num_of_trucks);
    //    this->computeDistances();
    auto start = std::chrono::high_resolution_clock().now();
    std::vector<Depot> tmp_solution;
    while (true) {
    assigning:
	auto current = std::chrono::high_resolution_clock().now();
	auto duration =
	    std::chrono::duration_cast<std::chrono::seconds>(current - start);
	// wait 4m 30s until exiting
	if (duration.count() > 4*60 + 30) {
	    std::cout << "Time's up!" << std::endl;
	    return;
	}
	std::cout<<duration.count()<<std::endl;
	this->assignDepotsToTrucks(15);
	for (auto &truck : this->trucks) {
	    tmp_solution = truck.solveAnnealing(start_depot);
	    
	    if (tmp_solution.size() == 1 && tmp_solution[0].num == -1) {
		// the assignment is bad, so break the loop and return to assigning
		this->solution.clear();
		tmp_solution.clear();
		goto assigning;
	    }
	    this->solution.push_back(tmp_solution);
	    tmp_solution.clear();
        }
	break;
    }
    return;
}
