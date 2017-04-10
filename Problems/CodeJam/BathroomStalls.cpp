#include <cstdio>
#include <iostream>

using llp = std::pair<long long, long long>;

llp get_mm(long long n, long long k)
{
	if (k == 1)
	{
		return llp(n/2, (n-1)/2);
	}

	if (n % 2 == 1)
	{
		return get_mm(n/2, k/2);
	}
	else
	{
		if (k % 2 == 1)
		{
			return get_mm((n-1)/2, k/2);
		}
		else
		{
			return get_mm(n/2, k/2);
		}
	}
}

int main()
{
	FILE *fin, *fout;
	freopen_s(&fin, "CodeJam\\BathroomStalls_in.txt", "r", stdin);
	freopen_s(&fout, "CodeJam\\BathroomStalls_out.txt", "w", stdout);

	int t;
	scanf_s("%d", &t);

	for (int i = 1; i <= t; ++i)
	{
		long long n, k;
		scanf_s("%lld %lld", &n, &k);

		auto p = get_mm(n, k);
		printf("Case #%d: %lld %lld\n", i, p.first, p.second);
	}

	return 0;
}
