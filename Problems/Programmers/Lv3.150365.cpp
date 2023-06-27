#include <string>
#include <vector>
#include <cmath>

using namespace std;

bool is_possible(int n, int m, int x, int y, int r, int c, int k)
{
    int dist = (abs(r-x) + abs(c-y));
    return (k >= dist && (k - dist) % 2 == 0);
}
bool can_down(int n, int m, int x, int y, int r, int c, int k)
{
    return x+1 <= n && is_possible(n, m, x+1, y, r, c, k-1);
}
bool can_left(int n, int m, int x, int y, int r, int c, int k)
{
    return y-1 >= 1 && is_possible(n, m, x, y-1, r, c, k-1);
}
bool can_right(int n, int m, int x, int y, int r, int c, int k)
{
    return y+1 <= n && is_possible(n, m, x, y+1, r, c, k-1);
}
bool can_up(int n, int m, int x, int y, int r, int c, int k)
{
    return x-1 >= 1 && is_possible(n, m, x-1, y, r, c, k-1);
}
string solution(int n, int m, int x, int y, int r, int c, int k)
{
    string answer = "";
    while(k > 0)
    {
        if (can_down(n, m, x, y, r, c, k))
        {
            ++x; --k;
            answer += 'd';
            continue;
        }
        if (can_left(n, m, x, y, r, c, k))
        {
            --y; --k;
            answer += 'l';
            continue;
        }
        if (can_right(n, m, x, y, r, c, k))
        {
            ++y; --k;
            answer += 'r';
            continue;
        }
        if (can_up(n, m, x, y, r, c, k))
        {
            --x; --k;
            answer += 'u';
            continue;
        }
        return "impossible"s;
    }
    
    return answer;
}