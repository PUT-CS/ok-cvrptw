#include <algorithm>
#include <cstdio>
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

        int rand_idx = rand_int_in_range_inclusive(1, tmp_depot_vec.size()-1);
        
        // assing the depot, mark it as assigned by removing from tmp_depot_vec
        this->trucks[current_truck_idx].assignment.push_back(tmp_depot_vec[rand_idx]);

        // remove rand_idx from tmp_depot_vec;
        tmp_depot_vec.erase(tmp_depot_vec.begin()+rand_idx);

        current_truck_idx = (current_truck_idx+1) % max_truck_idx;
    }
}

void Problem::solveAnnealing(int INITIAL_TEMP, int MIN_TEMP, float COOLING_RATE, int MAX_NEIGHBORS) {
    // depot 0 never gets assigned!
    int used_trucks = this->num_of_trucks;
    auto start = std::chrono::high_resolution_clock().now();
    std::vector<Depot> tmp_solution;
    std::vector<std::vector<Depot>> tmp_all_solution;
    std::vector<std::vector<Depot>> best_all_solution;
    while (used_trucks > 3) {
        tmp_all_solution.clear();
        auto start_of_truck_num_iter = std::chrono::high_resolution_clock().now();
        //std::cout<<used_trucks<<"\n";
    assigning:
        auto current = std::chrono::high_resolution_clock().now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(current - start);
        auto duration_of_truck_num_iter = std::chrono::duration_cast<std::chrono::seconds>(current - start_of_truck_num_iter);
        // wait 4m 30s until exiting
        if (duration.count() > 4*60 + 30) {
            fprintf(stderr, "Time's up (4m30s)\n");
            return;
        }

        if (duration_of_truck_num_iter.count() > 15) {
            fprintf(stderr, "Time for a truck number iteration exceeded (15s)\n");
            break;
        }
        this->assignDepotsToTrucks(used_trucks);
        for (auto &truck : this->trucks) {

            tmp_solution = truck.solveAnnealing(start_depot, INITIAL_TEMP, MIN_TEMP, COOLING_RATE, MAX_NEIGHBORS);
            if (tmp_solution.size() == 1 && tmp_solution[0].num == -1) {
                // the assignment is bad, so break the loop and return to assigning, clear the vectors
                this->solution.clear();
                tmp_solution.clear();
                goto assigning;
            }
            tmp_all_solution.push_back(tmp_solution);
            tmp_solution.clear();
        }
        // on first iteration, assign current as best
        if (used_trucks == this->num_of_trucks) {
            best_all_solution = tmp_all_solution;
        }
        if (total_solution_value(tmp_all_solution) < total_solution_value(best_all_solution)) {
            best_all_solution = tmp_all_solution;
        }
        used_trucks-- ;
    }
    this->solution = best_all_solution;
    return;
}

void Problem::computeSolutionValue() {
    for (auto &sol : this->solution) {
        if (sol.empty())
            continue;
        this->routes++;
        this->solution_sum += objective_function(sol);
    }
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

void Problem::printSolution() {
    std::cout<<this->routes<<" "<<this->solution_sum<<"\n";
    for (auto &solution_vec : this->solution) {
        if (solution_vec.empty())
            continue;
        for (auto &depot : solution_vec) {
            std::cout << depot.num << " ";
        }
        std::cout<<"\n";
    }
}

void Problem::saveSolutionToFile(char* name) {
    std::ofstream out;
    out.open(name);
    out<<this->routes<<" "<<this->solution_sum<<"\n";
    for (auto &solution_vec : this->solution) {
        if (solution_vec.empty())
            continue;
        for (auto &depot : solution_vec) {
            out << depot.num << " ";
        }
        out << "\n";
    }
    out.close();
}

void Problem::save(int argc, char* argv[]) {
    //    if (argc == 3) {
    //        this->saveSolutionToFile(argv[2]);
    //        return;
    //    }
    this->printSolution();
    return;
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
        for (int i = 0; i<num_of_trucks; i++) {
            trucks.push_back(Truck(truck_capacity));
        }
        this->depots.pop_back();
        input.close();
}

