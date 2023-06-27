using namespace std;

long long max(long long l1, long long l2) { return l1 > l2 ? l1 : l2; }
long long solution(int price, int money, int count)
{
    long long total_cost = 0ll;
    for(int i = 1; i <= count; ++i)
        total_cost += static_cast<long long>(price) * i;
    
    return max(0ll, total_cost - money);
}