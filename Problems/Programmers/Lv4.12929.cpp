#include <map>
using namespace std;

map<pair<int, int>, int> saved;

int find_comb(int open, int close)
{
    if (open > close) return 0;
    if (open == 0) return 1;
    
    if (auto it = saved.find(make_pair(open, close)); it != saved.end())
        return it->second;
    
    int sum = 0;
    for (int i = open; i >= 0; --i)
        sum += find_comb(open - i, close - 1);
    
    saved.emplace(make_pair(open, close), sum);
    return sum;
}

int solution(int n)
{
    return find_comb(n, n);
}