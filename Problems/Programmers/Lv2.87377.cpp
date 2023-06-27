#include <string>
#include <vector>
#include <set>
#include <utility>
#include <limits>
#include <algorithm>

using namespace std;
using point = pair<long long, long long>;

void find_point_list(const vector<vector<int>>& line, set<point>& out_point_list)
{
    for (int i = 0; i < line.size(); ++i)
    {
        for (int j = i+1; j < line.size(); ++j)
        {
            const vector<int>& coeff1 = line[i];
            const vector<int>& coeff2 = line[j];
            
            long long a = coeff1[0], b = coeff1[1], e = coeff1[2];
            long long c = coeff2[0], d = coeff2[1], f = coeff2[2];
            long long xnum = (b*f-e*d), ynum = (e*c-a*f), dev = (a*d-b*c);
            if (dev == 0) continue;
            if (xnum % dev != 0) continue;
            if (ynum % dev != 0) continue;
            out_point_list.emplace(xnum/dev, ynum/dev);
        }
    }
}
void find_side_point(const set<point>& point_list, long long& out_left, long long& out_right, long long& out_top, long long& out_bottom)
{
    out_left = out_bottom = numeric_limits<long long>::max();
    out_right = out_top = numeric_limits<long long>::min();
    for (const point& p : point_list)
    {
        out_left = min(out_left, p.first);
        out_right = max(out_right, p.first);
        out_top = max(out_top, p.second);
        out_bottom = min(out_bottom, p.second);
    }
}
vector<string> solution(vector<vector<int>> line)
{
    set<point> point_list;
    find_point_list(line, point_list);

    long long left, right, top, bottom;
    find_side_point(point_list, left, right, top, bottom);

    vector<string> answer;
    for (long long i = top; i >= bottom; --i)
    {
        string row;
        for (long long j = left; j <= right; ++j)
        {
            row += (point_list.find(make_pair(j, i)) != point_list.end() ? '*' : '.');
        }
        answer.emplace_back(row);
    }
    return answer;
}