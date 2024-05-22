#include <iostream>
#include <fstream>
#include "Station.h"
#include "Path.h"
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
int main()
{
    ifstream infile("metro.csv");
    Path p(infile);
    cout << "Enter starting station,Line *-ending station,Line *:" << endl;
    p.read_start_end(cin);
    if (!p.is_valid())
    {
        cout << "Start/End station not included in the metro map" << endl;
        return 1;
    }
    cout << "Finding route..." << endl;
    if (p.find_path())
    {
        cout << "====Route found====" << endl;
        p.optimize();
        p.output();
    }
    else
    {
        cout << "====No route found====" << endl;
    }
    return 0;
}
