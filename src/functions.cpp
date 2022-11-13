#include "functions.h"
#include "Depot.h"
#include <math.h>

double dist(Depot d1, Depot d2) {
    return std::sqrt(pow((d2.x-d1.x), 2) + std::pow((d2.y-d1.y), 2));
}


// the solution passed to this function always has to be feasible!
double objective_function(std::vector<Depot> solution) {
    if (solution.empty()) {
	std::cout<<"Empty solution passed to OF"<<std::endl;
	return 0;
    }
    double time = 0;

    // start at the magazine
    Depot current_depot = solution[0];
    Depot next_depot;
    
    // this segfaults
    for (unsigned long int i = 0; i<solution.size(); i++) {
	// select the target depot
	next_depot = solution[i];

	// add the travel distance
	time += dist(current_depot, next_depot);

	// go from the current town to the next depot
	current_depot = next_depot;

	// the truck came too early so we fast forward the time
	if (time < current_depot.ready_time) {
	    time = current_depot.ready_time;
	}

	// serve the depot
	time += current_depot.service_duration;
    }

    return time;
}

void print_depot_vec(std::vector<Depot> &v) {
    using std::cout, std::endl;
    for (auto &d : v) {
	cout<<d.num<<" ";
    }
    cout<<endl;
}
