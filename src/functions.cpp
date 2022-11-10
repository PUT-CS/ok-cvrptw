#include "functions.h"
#include "Depot.h"
#include <math.h>

double dist(Depot d1, Depot d2) {
    return std::sqrt(pow((d2.x-d1.x), 2) + std::pow((d2.y-d1.y), 2));
}

double objective_function(std::vector<Depot> solution) {
    double value = 0;

    // start at the magazine
    Depot current_depot = solution[0];

    // 
    for (int i=1; i<solution.size(); i++) {
	value += dist(current_depot, solution[i]);
	current_depot = solution[i];
    }
    return value;
}
