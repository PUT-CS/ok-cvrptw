#include "Problem.h"
#include <iostream>
#include <fstream>
#include <cmath>
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
	for (auto &depot : this->depots) {
	    depot.dist = dist(this->start_depot.x, this->start_depot.y, depot.x, depot.y);
	    depot.angle = slope_in_deg(this->start_depot.x, this->start_depot.y, depot.x, depot.y);
	}
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
    }
