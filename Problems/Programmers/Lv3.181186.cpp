#include <string>
#include <vector>

using namespace std;
constexpr long long mod = 1000000007;

long long comb(int n)
{
    // f(n) = f(n-1)*1 + f(n-2)*2 + f(n-3)*5
    //      +(f(n-4) + f(n-7) + f(n-10) + ... ) * 2
    //      +(f(n-5) + f(n-8) + f(n-11) + ... ) * 2
    //      +(f(n-6) + f(n-9) + f(n-12) + ... ) * 4
    // g(n) = f(n) + f(n-3) + ...
    vector<long long> f(n+1, 0ll);
    vector<long long> g(n+1, 0ll);
    f[0] = 1; g[0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        if (i >= 1) f[i] += f[i-1] * 1;
        if (i >= 2) f[i] += f[i-2] * 2;
        if (i >= 3) f[i] += f[i-3] * 5;
        if (i >= 4) f[i] += g[i-4] * 2;
        if (i >= 5) f[i] += g[i-5] * 2;
        if (i >= 6) f[i] += g[i-6] * 4;
        
        if (i >= 1) g[i] += f[i];
        if (i >= 3) g[i] += g[i-3];
        
        f[i] %= mod;
        g[i] %= mod;
    }
    
    //for (int i = 0; i <= n; ++i) printf("f(%d) = %lld\n", i, f[i]);
    //for (int i = 0; i <= n; ++i) printf("g(%d) = %lld\n", i, g[i]);
    
    return f[n];
}

int solution(int n)
{
    return comb(n) % mod;
}