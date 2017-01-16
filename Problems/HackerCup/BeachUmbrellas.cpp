#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>

const int mod = 1000000007;

int get_total_ways(std::vector<int>& radiuses, const int points);

int main()
{
	int t;
	std::cin >> t;

	for (int i = 1; i <= t; ++i)
	{
		int n, m;
		std::cin >> n >> m;

		std::vector<int> radiuses;
		while(n--)
		{
			int r;
			std::cin >> r;

			radiuses.emplace_back(r);
		}

		int answer = get_total_ways(radiuses, m);

		std::cout << "Case #" << i << ": " << answer << std::endl;
	}
	
	return 0;
}

int modpow(long long n, long long p)
{
	int acc = 1;
	while(p)
	{
		n %= mod;
		if (p % 2 == 1)
			acc = (n * acc) % mod;
		n *= n;
		p /= 2;
	}

	return acc;
}

int inverse(int denom)
{
	int inv = modpow(denom, mod - 2);
	return inv;
}

int comb(int n, int r)
{
	long long num = 1, denom = 1;
	for (int i = 0; i < r; ++i)
	{
		num *= (n - i);
		denom *= (r - i);

		num %= mod;
		denom %= mod;
	}
	
	return (num * inverse(denom % mod)) % mod;
}

int fact(int n)
{
	long long f = 1;
	for (int i = n; i >= 2; --i)
	{
		f *= i;
		f %= mod;
	}

	return f % mod;
}

int get_total_ways(std::vector<int>& radiuses, const int points)
{
	std::sort(radiuses.begin(), radiuses.end(), std::greater<int>());

	int sum_of_radiuses = std::accumulate(radiuses.begin(), radiuses.end(), 0);
	int total_length = sum_of_radiuses * 2 + 1;
	int count = radiuses.size();

	int total_ways = 0;
	if (count == 1)
	{
		int total_points = points + 2 * radiuses[0];
		int remain_points = total_points - total_length;
		int ways = remain_points + 1;
		total_ways = (total_ways + ways) % mod;
	}
	else
	{
		for (int i = 0; i < count; ++i)
		{
			for (int j = i+1; j < count; ++j)
			{
				int total_points = points + radiuses[i] + radiuses[j];
				int remain_points = total_points - total_length;
				if (remain_points < 0)
				{
					break;
				}

				int ways = (static_cast<long long>(comb(remain_points + count, count)) * 2 * fact(count - 2)) % mod;
				total_ways = (total_ways + ways) % mod;
			}
		}
	}

	return total_ways;
}
