#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

long long solution(int cap, int n, vector<int> deliveries, vector<int> pickups)
{
    long long answer = 0;
    
    int remain_d = 0, remain_p = 0;
    while(--n >= 0)
    {
        int d = max(0, deliveries[n] - remain_d);
        int p = max(0, pickups[n] - remain_p);
        remain_d = max(0, remain_d - deliveries[n]);
        remain_p = max(0, remain_p - pickups[n]);
        if (d == 0 && p == 0)
        {
            continue;
        }
        
        int shuttle_d = (d / cap + (d % cap == 0 ? 0 : 1));
        int shuttle_p = (p / cap + (p % cap == 0 ? 0 : 1));
        int shuttle = max(shuttle_d, shuttle_p);
        remain_d += shuttle * cap - d;
        remain_p += shuttle * cap - p;
        answer += shuttle * 2 * (n+1);
    }
    
    return answer;
}