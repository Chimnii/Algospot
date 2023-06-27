#include <iostream>
#include <string>
#include <vector>

using namespace std;
struct coord
{
    int sn = 0, ew = 0;
    coord(int _sn, int _ew) : sn(_sn), ew(_ew) {}
    coord& operator+= (const coord& other) { sn += other.sn; ew += other.ew; return *this; }
};

coord find_starting_point(const vector<string>& park)
{
    for (int sn = 0; sn < park.size(); ++sn)
    {
        for (int ew = 0; ew < park[sn].length(); ++ew)
        {
            if (park[sn][ew] == 'S')
                return coord(sn, ew);
        }
    }
    //cout << "cannot find starting point" << endl;
    return coord(0, 0);
}

bool is_arrivable(const vector<string>& park, const coord& start, coord dir, int dist)
{
    coord current = start;
    while (dist--)
    {
        current += dir;
        if (current.sn >= park.size())
            return false;
        if (current.ew >= park[current.sn].length())
            return false;
        if (park[current.sn][current.ew] == 'X')
            return false;
    }
    return true;
}

void parse_route(const string& route, coord& out_dir, int& out_dist)
{
    if (route.length() < 3)
        return;
    char dir = route[0];

    out_dir.sn = (dir == 'S' ? 1 : dir == 'N' ? -1 : 0);
    out_dir.ew = (dir == 'E' ? 1 : dir == 'W' ? -1 : 0);
    out_dist = static_cast<int>(route[2] - '0');
}

vector<int> solution(vector<string> park, vector<string> routes)
{
    coord current = find_starting_point(park);
    //cout << "current " << current.sn << ", " << current.ew << endl;
    for (const string& route : routes)
    {
        coord dir(0, 0);
        int dist;
        parse_route(route, dir, dist);

        if (is_arrivable(park, current, dir, dist))
        {
            current += coord(dir.sn * dist, dir.ew * dist);
        }
        //cout << "current " << current.sn << ", " << current.ew << endl;
    }

    vector<int> answer = { current.sn, current.ew };
    return answer;
}
