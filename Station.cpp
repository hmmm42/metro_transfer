#include "Station.h"
#include <sstream>
#include <iostream>
using std::string;
Station::Station() : name(""), line(""), visited(false), transfer1(0), transfer2(0) {}
Station::Station(const string &name, const string &line, int transfer1, int transfer2) : name(name), line(line), visited(false), transfer1(transfer1), transfer2(transfer2) {}
bool operator==(const Station &lhs, const Station &rhs)
{
    return lhs.get_name() == rhs.get_name();
}
