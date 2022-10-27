#include "Depot.h"
void Depot::print(){
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
