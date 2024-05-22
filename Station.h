#ifndef GUARD_STATION_H
#define GUARD_STATION_H
#include <iostream>
class Station
{
public:
    Station();
    Station(const std::string &name, const std::string &line, int transfer1, int transfer2);
    std::string get_name() const { return name; }
    std::string get_line() const { return line; }
    int get_transfer1() const { return transfer1; }
    int get_transfer2() const { return transfer2; }
    bool is_visited() const { return visited; }
    void set_visited(bool v) { visited = v; }

private:
    std::string name;
    std::string line;
    int transfer1;
    int transfer2;
    bool visited;
};

// 判断两个站点是否相同
bool operator==(const Station &lhs, const Station &rhs);

#endif