#include "Path.h"
using std::cout;
using std::endl;
using std::getline;
using std::istream;
using std::string;
using std::vector;
Path::Path() : start(), end() {}
Path::Path(vector<Station> path) : path(path) {}
Path::Path(istream &is)
{
    try
    {
        string temp;
        getline(is, temp);
        string line;
        while (getline(is, line))
        {
            if (!line.empty())
            {
                std::stringstream ss(line);
                string id, name, line_no, transfer_id1, transfer_id2;
                getline(ss, id, ',');
                getline(ss, name, ',');
                getline(ss, line_no, ',');
                getline(ss, transfer_id1, '/');
                getline(ss, transfer_id2);
                int transfer1 = 0;
                int transfer2 = 0;
                if (!transfer_id1.empty())
                {
                    try
                    {
                        transfer1 = std::stoi(transfer_id1);
                    }
                    catch (const std::invalid_argument &)
                    {
                        transfer1 = 0;
                    }
                }
                if (!transfer_id2.empty())
                {
                    try
                    {
                        transfer2 = std::stoi(transfer_id2);
                    }
                    catch (const std::invalid_argument &)
                    {
                        transfer2 = 0;
                    }
                }

                Station s(name, line_no, transfer1, transfer2);
                path.push_back(s);
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error initializing Path: " << e.what() << endl;
    }
}
void Path::read_start_end(istream &is)
{
    string n, l;

    getline(is, n, ',');
    getline(is, l, '-');
    start = Station(n, l, 0, 0);

    getline(is, n, ',');
    getline(is, l);
    end = Station(n, l, 0, 0);
}

void Path::dfs(vector<Station> &current_path, Station &current)
{
    for (const auto &station : current_path)
    {
        if (station == current && station.get_line() == current.get_line())
        {
            return; // 如果当前站点已在路径中，直接返回
        }
    }
    current.set_visited(true);       // 标记当前站点为已访问
    current_path.push_back(current); // 将当前站点加入当前路径

    if (current == end)
    { // 如果当前站点是终点站
        if (transfer_lines.empty() || current_path.size() < transfer_lines.size())
        {
            transfer_lines = current_path; // 更新最短路径
        }
        current_path.pop_back(); // 从当前路径中移除当前站点
        return;
    }
    current.set_visited(true); // 标记当前站点为已访问
    for (auto &s : path)
    {
        if (s.is_visited() == 0 &&
            (s.get_line() == current.get_line() ||
             (s.get_transfer1() != 0 && path[s.get_transfer1() - 1].get_name() == current.get_name()) ||
             (s.get_transfer2() != 0 && path[s.get_transfer2() - 1].get_name() == current.get_name()) ||
             (s == current && s.get_line() != current.get_line())))
        {
            dfs(current_path, s); // 递归调用DFS
        }
    }
    current_path.pop_back(); // 从当前路径中移除当前站点
}

bool Path::find_path()
{
    for (auto &s : path)
    {
        s.set_visited(false); // 初始化所有站点为未访问状态
    }

    vector<Station> initial_path; // 初始路径为空
    start.set_visited(true);      // 标记起点站为已访问
    dfs(initial_path, start);     // 调用DFS查找路径

    return !transfer_lines.empty(); // 返回是否找到路径
}

bool Path::is_valid() const
{
    bool start_found = false;
    bool end_found = false;

    for (const auto &s : path)
    {
        if (s == start)
            start_found = true;
        if (s == end)
            end_found = true;
    }

    return start_found && end_found;
}
void Path::optimize()
{
    if (transfer_lines.empty())
    {
        return;
    }

    vector<Station> optimized;
    optimized.push_back(transfer_lines.front());

    for (size_t i = 1; i < transfer_lines.size(); ++i)
    {
        if (transfer_lines[i].get_line() == optimized.back().get_line() || transfer_lines[i].get_line() == transfer_lines[i + 1].get_line())
        {
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
