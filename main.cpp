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

