#include "Path.h"
using std::cout;
using std::endl;
using std::getline;
using std::istream;
using std::string;
using std::vector;
// Path::Path() : start(), end() {}
// Path::Path(vector<Station> path) : path(path) {}
// Path::Path(istream &is)
// {
//     string l;
//     getline(is, l);
//     while (is)
//     {
//         string temp;
//         getline(is, temp, ',');
//         Station s(is);
//         path.push_back(s);
//     }
// }
// void Path::read_start_end(istream &is)
// {
//     string n,l;
//     getline(is, n, ',');
//     getline(is, l, '-');
//     start = Station(n,l);
//     getline(is, n, ',');
//     getline(is, l);
//     end = Station(n,l);
// } // explain: 读入起点和终点
Path::Path() : start(), end() {}
Path::Path(std::vector<Station> path) : path(path) {}
// Path::Path(std::istream &is)
// {
//     string temp;
//     getline(is, temp);
//     std::string l;
//     while (getline(is, l))
//     {
//         std::stringstream ss(l);
//         string id, name, line, transfer_id1, transfer_id2;
//         getline(ss, id, ',');
//         getline(ss, name, ',');
//         getline(ss, line, ',');
//         getline(ss, transfer_id1, '/');
//         getline(ss, transfer_id2);
//         if (transfer_id2.empty())
//         {
//             transfer_id2 = "0";
//         }
//         try {
//             Station s(name, line, std::stoi(transfer_id1), std::stoi(transfer_id2));
//             path.push_back(s);
//         } catch (std::invalid_argument& e) {
//             // std::cerr << "Invalid argument: " << e.what() << '\n';
//             continue;
//         }
       
//     }
// }
Path::Path(std::istream &is) {
    try {
        string temp;
        getline(is, temp);
        std::string line;
        while (getline(is, line)) {
            if (!line.empty()) {
                std::stringstream ss(line);
                std::string id, name, line_no, transfer_id1, transfer_id2;
                getline(ss, id, ',');
                getline(ss, name, ',');
                getline(ss, line_no, ',');
                getline(ss, transfer_id1, '/');
                getline(ss, transfer_id2);
                // Validate and convert transfer IDs
                int transfer1 = 0;
                int transfer2 = 0;
                if (!transfer_id1.empty()) {
                    try {
                        transfer1 = std::stoi(transfer_id1);
                    } catch (const std::invalid_argument &) {
                        transfer1 = 0; // default to 0 if conversion fails
                    }
                }
                if (!transfer_id2.empty()) {
                    try {
                        transfer2 = std::stoi(transfer_id2);
                    } catch (const std::invalid_argument &) {
                        transfer2 = 0; // default to 0 if conversion fails
                    }
                }

                // Create and add the station
                Station s(name, line_no, transfer1, transfer2);
                path.push_back(s);
            }
        }
    } catch (const std::exception &e) {
        std::cerr << "Error initializing Path: " << e.what() << std::endl;
    }
}
// void Path::read_start_end(std::istream &is) {
//     std::string n, l;
//     if (getline(is, n, ',') && getline(is, l, '-')) {
//         start = Station(n, l);
//     }
//     if (getline(is, n, ',') && getline(is, l)) {
//         end = Station(n, l);
//     }
// }
void Path::read_start_end(std::istream &is)
{
    std::string n, l;
    
    // Read start station
    getline(is, n, ',');
    getline(is, l, '-');
    start = Station(n, l,0,0);

    // Read end station
    getline(is, n, ',');
    getline(is, l);
    end = Station(n, l,0,0);
}
// bool Path::finding() {
//     if (transfer_lines.empty()) {
//         return false;
//     }
//     Station &current = transfer_lines.back();
//     std::cout << "当前站点: " << current.get_name() << ", " << current.get_line() << std::endl;
//     if (current == end) {
//         return true;
//     }
//     for (auto &s : path) {
//         if (s.is_visited()) {
//             continue;
//         }
//         if (s.get_line() == current.get_line() && s.get_name() != current.get_name()) {
//             continue;
//         }
//         bool can_transfer = false;
//         if ((s.get_transfer1() != 0 && s.get_transfer1() <= path.size() && path[s.get_transfer1() - 1].get_line() == current.get_line()) ||
//             (s.get_transfer2() != 0 && s.get_transfer2() <= path.size() && path[s.get_transfer2() - 1].get_line() == current.get_line())) {
//             can_transfer = true;
//         }
//         if (!can_transfer) {
//             continue;
//         }
//         s.set_visited(true);
//         transfer_lines.push_back(s);
//         if (finding()) {
//             return true;
//         }
//         transfer_lines.pop_back();
//         s.set_visited(false);
//     }
//     return false;
// }

// bool Path::find_path() {
//     for (auto &s : path) {
//         s.set_visited(false);
//     }

//     transfer_lines.clear();
//     transfer_lines.push_back(start);
//     start.set_visited(true);

//     // Debug output for start and end stations
//     std::cout << "起点站: " << start.get_name() << ", " << start.get_line() << std::endl;
//     std::cout << "终点站: " << end.get_name() << ", " << end.get_line() << std::endl;

//     if (finding()) {
//         return true;
//     }

//     // 清除状态并尝试反向查找
//     for (auto &s : path) {
//         s.set_visited(false);
//     }

//     transfer_lines.clear();
//     transfer_lines.push_back(end);
//     end.set_visited(true);

//     std::swap(start, end);

//     // Debug output for start and end stations (after swap)
//     std::cout << "起点站 (反向): " << start.get_name() << ", " << start.get_line() << std::endl;
//     std::cout << "终点站 (反向): " << end.get_name() << ", " << end.get_line() << std::endl;

//     bool found = finding();

//     // 恢复原始起点和终点
//     std::swap(start, end);

//     return found;
// }

void Path::dfs(vector<Station>& current_path, Station& current) {
    //输出current_path
    cout<<"current_path:"<<endl;
    for (const auto& station : current_path) {
        cout<<station.get_name()<<" "<<station.get_line()<<endl;
    }
    cout<<"current:"<<current.get_name()<<" "<<current.get_line()<<endl;
    cout<<endl;
    for (const auto& station : current_path) {
        if (station == current && station.get_line()==current.get_line()) {
            cout<<"return"<<endl;
            return;  // 如果当前站点已在路径中，直接返回
        }
    }
    current.set_visited(true);  // 标记当前站点为已访问
    current_path.push_back(current);  // 将当前站点加入当前路径

    std::cout << "当前站点: " << current.get_name() << ", " << current.get_line() << std::endl;
    cout<<current.get_transfer1()<<" "<<current.get_transfer2()<<endl;
    if (current == end) {  // 如果当前站点是终点站
        if (transfer_lines.empty() || current_path.size() < transfer_lines.size()) {
            transfer_lines = current_path;  // 更新最短路径
        }
        current_path.pop_back();  // 从当前路径中移除当前站点
        return;
    }
    current.set_visited(true);  // 标记当前站点为已访问 
    for (auto &s : path) {
        cout<<"push"<<" "<<s.get_name()<<" "<<s.get_line()<<" visited:"<<s.is_visited()<<endl;
        cout<<"is same station:"<< (s == current ? "true" : "false") <<endl;
        // if(end==s) continue;    
        if (s.is_visited()==0 && 
            (s.get_line() == current.get_line() ||
            (s.get_transfer1() != 0 && path[s.get_transfer1() - 1].get_name() == current.get_name()) ||
            (s.get_transfer2() != 0 && path[s.get_transfer2() - 1].get_name() == current.get_name()) ||
            (s == current && s.get_line() != current.get_line()))) 
            {
                cout<<"dfs"<<endl;
                s.set_visited(true);  // 标记当前站点为已访问
                dfs(current_path, s);  // 递归调用DFS
            }
    }
    
    cout<<"pop"<<endl;
    current_path.pop_back();  // 从当前路径中移除当前站点
    // current.set_visited(false);  // 标记当前站点为未访问

}


bool Path::find_path() {
    for (auto &s : path) {
        s.set_visited(false);  // 初始化所有站点为未访问状态
    }

    std::vector<Station> initial_path;  // 初始路径为空
    start.set_visited(true);  // 标记起点站为已访问
    dfs(initial_path, start);  // 调用DFS查找路径

    return !transfer_lines.empty();  // 返回是否找到路径
}

bool Path::is_valid() const
{
    bool start_found = false;
    bool end_found = false;

    for (const auto &s : path)
    {
        if (s == start)     start_found = true;
        if (s == end)       end_found = true;
    }

    return start_found && end_found;
}
void Path::optimize(){
    if (transfer_lines.empty()) {
        return;
    }

    std::vector<Station> optimized;
    optimized.push_back(transfer_lines.front());

    for (size_t i = 1; i < transfer_lines.size(); ++i) {
        if (transfer_lines[i].get_line() == optimized.back().get_line()
            || transfer_lines[i].get_line() == transfer_lines[i+1].get_line()){
            optimized.push_back(transfer_lines[i]);
        }
    }

    transfer_lines = optimized;

}


void Path::output() const
{
    for (size_t i = 0; i < transfer_lines.size(); ++i)
    {
        if (i > 0 && transfer_lines[i].get_line() != transfer_lines[i - 1].get_line())
        {
            cout << "Transfer:" << endl;
        }

        cout << transfer_lines[i].get_name() << ", " << transfer_lines[i].get_line() << endl;
    }
   
}
