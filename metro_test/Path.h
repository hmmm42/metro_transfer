#ifndef GUARD_PATH_H
#define GUARD_PATH_H
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <queue>
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
    void test_output() const{
        for (auto &s : path)
        {
            std::cout << s.get_name() << std::endl;
        }
    
    }

private:
    void dfs(std::vector<Station> &current_path, Station &current);
    std::vector<Station> path;
    Station start;
    Station end;
    //起点到终点的换乘线路
    std::vector<Station> transfer_lines;
    // bool finding();
};


#endif