#include "Station.h"
#include <sstream>
#include <iostream>
using std::cin;
using std::getline;
using std::istream;
using std::string;
using std::map;
Station::Station() : name(""), line(""), visited(false), transfer1(0), transfer2(0) {}
Station::Station(const string &name, const string &line, int transfer1, int transfer2) : name(name), line(line), visited(false), transfer1(transfer1), transfer2(transfer2) {}
// Station::Station(const std::string &line) :name(""), line(""), visited(false), transfer1(-1), transfer2(-1) {
//     std::istringstream ss(line);
//     std::string id, transfer_ids;
//     getline(ss, id, ',');
//     getline(ss, name, ',');
//     getline(ss, this->line, ',');
//     getline(ss, transfer_ids, ',');

//     // Parse transfer IDs if present
//     if (!transfer_ids.empty()) {
//         std::istringstream transfer_ss(transfer_ids);
//         std::string transfer_id;
//         if (getline(transfer_ss, transfer_id, '/')) {
//             try {
//                 transfer1 = std::stoi(transfer_id);
//             } catch (const std::invalid_argument&) {
//                 transfer1 = -1;  // Invalid transfer ID
//             }
//         }
//         if (getline(transfer_ss, transfer_id, '/')) {
//             try {
//                 transfer2 = std::stoi(transfer_id);
//             } catch (const std::invalid_argument&) {
//                 transfer2 = -1;  // Invalid transfer ID
//             }
//         }
//     }
// }

// Station::Station(const std::string &name, const std::string &line) : name(name), line(line), visited(false), transfer1(0), transfer2(0) {}


// // 示例:Guoquan Road,Line 10,3/14 读的时候忽略第一个序号，只读取站点名，线路，换乘线路，同时忽略逗号
// void Station::read(istream &is)
// {
//     getline(is, name, ','); // 读取站点名,直到遇到逗号
//     getline(is, line, ','); // 读取站点名,直到遇到逗号
//     is >> transfer1;         // 读取换乘线路
//     if (is.peek() == '/')   // 如果下一个字符是'/'，则读取第二个换乘线路
//     {
//         char c;
//         is >> c >> transfer2;
//     }
// }
bool operator==(const Station &lhs, const Station &rhs)
{
    return lhs.get_name() == rhs.get_name();
}

