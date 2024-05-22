#ifndef GUARD_STATION_H
#define GUARD_STATION_H
#include <iostream>
#include <map>
class Station
{
public:
    Station();
    // Station(const std::string &name, const std::string &line);
    Station(const std::string &name, const std::string &line, int transfer1, int transfer2);
    // Station(std::istream &is) { read(is); }
    std::string get_name() const { return name; }
    std::string get_line() const { return line; }
    int get_transfer1() const { return transfer1; }
    int get_transfer2() const { return transfer2; }
    bool is_visited() const { return visited; }
    void set_visited(bool v) { visited = v; }
    // 从用户输入中读入站点信息
    // void read(std::istream &is);
    // 设置站点的访问状态
private:
    std::string name;
    std::string line;
    // 换乘路线及线路(可能有两个换乘路线)
    int transfer1;
    int transfer2;
    // 访问标志
    bool visited;
};

// 判断两个站点是否相同
bool operator==(const Station &lhs, const Station &rhs);

#endif