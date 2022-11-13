#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Depot.h"
#include <vector>
double dist(Depot d1, Depot d2);
double objective_function(std::vector<Depot> solution);
void print_depot_vec(std::vector<Depot> &v);
#endif
