#include "functions.h"
#include "Depot.h"
#include <algorithm>
#include <math.h>
#include <random>
#include <vector>

double dist(Depot d1, Depot d2) {
    return std::sqrt(pow((d2.x-d1.x), 2) + std::pow((d2.y-d1.y), 2));
}

// the solution passed to this function always has to be feasible!
double objective_function(std::vector<Depot> solution) {
    if (solution.empty()) {
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

double total_solution_value(std::vector<std::vector<Depot>> sol) {
    double total = 0;
    for (auto &subsol : sol) {
        total += objective_function(subsol);
    }
    return total;
}

std::vector<Depot> get_neighboring_solution(std::vector<Depot> input, Depot start, int cargo) {
    std::vector<Depot> neighbor(input);
    int len = neighbor.size();
    if (len <= 3) {
        return input;
    }
 rolling:
    int a_idx = rand_int_in_range_inclusive(1, len-2);
    int b_idx = rand_int_in_range_inclusive(1, len-2);
    if (a_idx == b_idx)
        goto rolling;
    
    // swap two random elements
    std::iter_swap(neighbor.begin()+a_idx, neighbor.begin() + b_idx);
    if (!is_solution_feasible(start, neighbor, cargo)) {
        return input;
    }
    return neighbor;
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
    Depot next_depot;
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

        // the truck came too late
        if (time > current_depot.end_time) {
            return false;
        }

        // there's not enough cargo to serve the depot
        if (cargo < current_depot.demand) {
            return false;
        }

        // unload the truck
        time += current_depot.service_duration;
        
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
    int iter_limit = 100;
    while (!is_solution_feasible(start, v, capacity) && iter_limit --> 0) {
        std::shuffle(v.begin()+1, v.end()-1, gen);
    }
    if (iter_limit <= 0) {
        Depot d;
        d.num = -1;
        std::vector<Depot> x{d};
        return x;
    }
    return v;
}

void print_depot_vec(std::vector<Depot> &v) {
    using std::cout, std::endl;
    for (auto &d : v) {
        cout<<d.num<<" ";
    }
    cout<<endl;
}

void skip(std::ifstream &file, int n) {
    std::string buf;
    for (int i=0; i<n; i++)
        file>>buf;
}

int rand_int_in_range_inclusive(int min, int max) {
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(min, max); // define the range
    return distr(gen);
}
