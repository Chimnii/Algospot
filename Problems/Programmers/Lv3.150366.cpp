#include <string>
#include <vector>
#include <set>

using namespace std;

struct point
{
    int x, y;
    point() : x(0), y(0) {}
    point(int _x, int _y) : x(_x), y(_y) {}
    bool operator<(const point& other) const { return (x < other.x ?  true : (x == other.x ? y < other.y : false)); }
};

struct cell
{
    string value = ""s;
    cell* merged = nullptr;
    set<point> merged_list;
    void clear() { value = ""s; merged = nullptr; merged_list.clear(); }
};

class cell_container
{
public:
    void update(point p, const string& value)
    {
        find_cell(p).value = value;
    }
    void update(const string& from, const string& to)
    {
        for (int x = 1; x <= 50; ++x)
        {
            for (int y = 1; y <= 50; ++y)
            {
                point p(x, y);
                if (get_cell(p).value == from)
                    get_cell(p).value = to;
            }
        }
    }
    void merge(point p1, point p2)
    {
        cell& c1 = find_cell(p1);
        cell& c2 = find_cell(p2);
        if (&c1 == &c2)
            return;
        
        c1.value = c1.value.empty() ? c2.value : c1.value;
        
        if (c1.merged_list.empty()) c1.merged_list.emplace(p1);
        if (c2.merged_list.empty()) c2.merged_list.emplace(p2);
        
        set<point> merged_list = c2.merged_list;
        for (point p : merged_list)
        {
            get_cell(p).clear();
            get_cell(p).merged = &c1;
        }
        c1.merged_list.insert(merged_list.begin(), merged_list.end());
    }
    void unmerge(point p)
    {
        cell& merged = find_cell(p);
        
        set<point> merged_list = merged.merged_list;
        string merged_value = merged.value;
        
        for(point m : merged_list)
        {
            get_cell(m).clear();
        }
        get_cell(p).value = merged_value;
    }
    string print(point p)
    {
        string value = find_cell(p).value;
        return value.empty() ? "EMPTY"s : value;
    }
    void test()
    {
        for (int i = 1; i <= 4; ++i)
        {
            for (int j = 1; j <= 4; ++j)
            {
                printf("%s(%d) ", find_cell(point(i, j)).value.c_str(), cells[i][j].merged_list.size());
            }
            printf("\n");
        }
        
        printf("\n");
    }
    
private:
    cell& get_cell(point p)
    {
        return cells[p.x][p.y];
    }
    cell& find_cell(point p)
    {
        cell& c = get_cell(p);
        return c.merged ? *c.merged : c;
    }
    cell cells[51][51];
};

vector<string> split(const string& command, const string& token)
{
    vector<string> parsed;
    for (int i = 0; i < command.length();)
    {
        int f = command.find(token, i);
        f = (f == string::npos ? command.length() : f);
        parsed.emplace_back(command.substr(i, f - i));
        i = f + 1;
    }
    return parsed;
}
vector<string> solution(vector<string> commands)
{
    cell_container cells;
    
    vector<string> answer;
    for (const string& command : commands)
    {
        vector<string> s = split(command, " "s);
       if (s.size() == 0)
            continue;
        else if (s[0] == "UPDATE"s && s.size() == 4) cells.update(point(atoi(s[1].c_str()), atoi(s[2].c_str())), s[3]);
        else if (s[0] == "UPDATE"s && s.size() == 3) cells.update(s[1], s[2]);
        else if (s[0] == "MERGE"s && s.size() == 5) cells.merge(point(atoi(s[1].c_str()), atoi(s[2].c_str())), point(atoi(s[3].c_str()), atoi(s[4].c_str())));
        else if (s[0] == "UNMERGE"s && s.size() == 3) cells.unmerge(point(atoi(s[1].c_str()), atoi(s[2].c_str())));
        else if (s[0] == "PRINT"s && s.size() == 3) answer.emplace_back(cells.print(point(atoi(s[1].c_str()), atoi(s[2].c_str()))));
        
        printf("%s\n", command.c_str());
        cells.test();
    }
    return answer;
}