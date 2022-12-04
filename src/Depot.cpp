#include "Depot.h"
void Depot::print()
{
    using std::cout;
    using std::endl;
    cout << "ID: " << num << endl;
    cout << "X: " << x << ", "
         << "Y: " << y << endl;
    cout << "Demand: " << demand << endl;
    cout << "Ready: " << ready_time << ", Close: " << end_time << endl;
    cout << "Service Duration: " << service_duration << endl;
}
