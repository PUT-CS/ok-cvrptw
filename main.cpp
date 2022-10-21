#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>

using std::string;

class Depot {
public:
    int num, x, y, demand, ready_time, end_time, service_duration;
    Depot() {}
    ~Depot() {}
};

void skip(std::ifstream &file, int n) {
    string buf;
    for (int i=0; i<n; i++)
	file>>buf;
}

class Problem {
public:
    int num_of_trucks, truck_capacity;
    std::vector<Depot> depots;
    
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
    return 0;
}
