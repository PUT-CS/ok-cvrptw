#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Depot.h"
#include <fstream>
#include <vector>
#include <deque>
double dist(Depot d1, Depot d2);
double objective_function(std::vector<Depot>& solution);
std::vector<Depot> get_neighboring_solution(std::vector<Depot>& input,
    Depot start, int cargo);
float choose_worse_solution(float temperature, std::vector<Depot>& prev,
    std::vector<Depot>& next);
float roll();
bool is_solution_feasible(Depot start, std::vector<Depot>& solution, int cargo);
double total_solution_value(std::vector<std::vector<Depot>> sol);
std::vector<Depot> get_initial_solution(std::vector<Depot>& assignment,
    int capacity, Depot start);
void skip(std::ifstream& file, int n);
void print_depot_vec(std::vector<Depot>& v);
int rand_int_in_range_inclusive(int min, int max);
std::vector<int> toIntVector(std::vector<Depot> &solution);
bool is_tabu(std::deque<std::vector<int>> tabuList, std::vector<int> neighbor);
#endif
