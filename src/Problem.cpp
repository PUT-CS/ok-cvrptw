#include <algorithm>
#include <iostream>
#include <fstream>
#include <cmath>
#include <ostream>
#include <vector>
#include <bits/stdc++.h>
#include "Problem.h"
#include "Truck.h"
#define PI 3.141593

void skip(std::ifstream &file, int n) {
    std::string buf;
    for (int i=0; i<n; i++)
	file>>buf;
}

double dist(double x1, double y1, double x2, double y2) {
    return std::sqrt(pow((x2-x1), 2) + std::pow((y2-y1), 2));
}

double slope_in_deg(double x1, double y1, double x2, double y2) {
    double res = std::atan((y2-y1)/(x2-x1));
    res = res*180/PI; // na stopnie
    // kompensacja za ćwiartki, zasięg wyniku = 0 -> 360
    if (x2 < x1) {
	res += 180;
    } else if (x1 <= x2 && y1 > y2) {
	res += 360;
    }
    return res;
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
	this->min_angle = 360.0;
	this->max_angle = 0.0;
	for (auto &depot : this->depots) {
	    depot.dist = dist(this->start_depot.x, this->start_depot.y, depot.x, depot.y);
	    depot.angle = slope_in_deg(this->start_depot.x, this->start_depot.y, depot.x, depot.y);
	    if (depot.angle < this->min_angle) {
		this->min_angle = depot.angle;
	    }
	    if (depot.angle > this->max_angle) {
		this->max_angle = depot.angle;
	    }
	}
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
		<<"angle="<<d.angle<<"\t"
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

void Problem::assignDepotsToTrucks() {
     std::vector<std::vector<float>> deg_ranges;
    double degs_to_cover =
	(this->max_angle - this->min_angle) / this->num_of_trucks;
    double first_a = this->min_angle, second_a = first_a + degs_to_cover;
    while (second_a < this->max_angle) {
	std::vector<float> v;
	v.push_back(first_a);
	v.push_back(second_a);
	deg_ranges.push_back(v);
	first_a = second_a;
	second_a += degs_to_cover;
	if (second_a + degs_to_cover > this->max_angle) {
	    second_a = this->max_angle;
	}
    }
    
    std::vector<float> f;
    f.push_back(first_a);
    f.push_back(second_a);
    deg_ranges.push_back(f);
    
    std::vector<std::vector<Depot>> truck_assignments;
    
    for (int i = 0; i<deg_ranges.size(); i++) {
	auto &range = deg_ranges[i];
	// now we need to split the depots into lists for each truck
	std::vector<Depot> tmp_assignment;
	for (auto &depot : this->depots) {
	    if (depot.angle >= range[0] && depot.angle < range[1]) {
		tmp_assignment.push_back(depot);
	    }
	}
	truck_assignments.push_back(tmp_assignment);
	this->trucks.at(i).assignment = tmp_assignment;
    }
}

void Problem::solveGreedy() {
    this->assignDepotsToTrucks();
    // the depots are split into lists for each of the trucks
    // now we need to solve the subproblem assigned to each truck
    for (auto &truck : this->trucks) {
	this->solution.push_back(truck.solveSubproblem(this->start_depot));
    }
    // the initial subproblem solving probably won't cover all of the depots.
    // now we can check for trucks that don't have any depots assigned
    // and assign them to those depots that couldn't be covered
    // however, if there are no free trucks left, we assume there's no viable solution.
    this->print();
    
    return;
}
