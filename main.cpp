#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <ostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#define PI 3.141593

using std::string;

class Depot {
public:
    int num, x, y, demand, ready_time, end_time, service_duration;
    double dist, angle;
    void print(){
	using std::cout, std::endl;
	cout<<std::setw(3)<<
	    this->num<<
	    this->x<<
	    this->y<<
	    this->demand<<
	    this->ready_time<<
	    this->end_time<<
	    this->service_duration<<
	    endl;
    }
    Depot() {}
    ~Depot() {}
};

void skip(std::ifstream &file, int n) {
    string buf;
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


class Problem {
public:
    int num_of_trucks, truck_capacity;
    std::vector<Depot> depots;
    Depot start_depot;
    
    void readFrom(std::string filename) {
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
    void print() {
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
};

int main(int argc, char* argv[]) {
    if (argc == 1) {
	printf("Please provide a file as an argument");
	exit(1);
    }
    Problem problem;
    problem.readFrom(argv[1]);
    problem.print();
    //std::cout<< "Each truck has " << 360.0/problem.num_of_trucks << " degrees to cover" << std::endl;
    double degs_to_cover = 360.0/problem.num_of_trucks;
    double first_a = 0.0, second_a = degs_to_cover;
    std::vector<std::vector<float>> deg_pairs;

    while (second_a < 360) {
	std::vector<float> v;
	v.push_back(first_a); v.push_back(second_a);
	deg_pairs.push_back(v);
	first_a = second_a;
	second_a += degs_to_cover;
	if (second_a + degs_to_cover > 360) {
	    second_a = 360;
	}
    }
    
    std::vector<float> f;
    f.push_back(first_a);
    f.push_back(second_a);
    deg_pairs.push_back(f);
    for (auto &element : deg_pairs) {
       	printf("%f -> %f\n", element[0], element[1]);
    }
    return 0;
}

