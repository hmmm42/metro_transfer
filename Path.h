#ifndef GUARD_PATH_H
#define GUARD_PATH_H
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "Station.h"
class Path
{
public:
    Path();
    Path(std::vector<Station> path);
    Path(std::istream &is);
    void read_start_end(std::istream &is);
    bool find_path();
    bool is_valid() const;
    void optimize();
    void output() const;

private:
    void dfs(std::vector<Station> &current_path, Station &current);
    std::vector<Station> path;
    Station start;
    Station end;
    std::vector<Station> transfer_lines;
};

#endif