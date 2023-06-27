using System;

public class Solution
{
    int div = 1000000007;
    long[,] saved = new long[101,101];
    public long find_comb(int n, int count)
    {
        if (n <= 0 || count <= 0) return 0;
        if (n == count) return 1;
        if (n < count) return 0;
        if (saved[n,count] != 0) return saved[n,count];
        
        long comb = find_comb(n-1, count) * (n-1) * 2 + find_comb(n-1, count-1);
        saved[n,count] = comb;
        return comb;
    }
    public int solution(int n, int count)
    {
        for(int i = 0; i < 101; ++i) for (int j = 0; j < 101; ++j) saved[i,j] = 0;
        
        //return find_comb(n, count);
        
        saved[1,1] = 1;
        for (int i = 2; i <= n; ++i)
        {
            for (int j = 1; j <= i; ++j)
            {
                saved[i,j] = saved[i-1,j] * (i-1) * 2 + saved[i-1,j-1];
                saved[i,j] %= div;
            }
        }
        return (int)(saved[n,count] % div);
    }
}
