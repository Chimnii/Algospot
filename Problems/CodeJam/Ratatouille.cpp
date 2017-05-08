#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>

int calc(const int n, const int p, const std::vector<int>& rs, const std::vector<std::vector<int>> qs);

int main()
{
	FILE *fin, *fout;
	freopen_s(&fin, "CodeJam\\Ratatouille_in.txt", "r", stdin);
	//freopen_s(&fout, "HackerCup\\Practice_out.txt", "w", stdout);

	int t;
	scanf_s("%d", &t);

	for (int i = 1; i <= t; ++i)
	{
		int n, p;
		scanf_s("%d %d", &n, &p);

		std::vector<int> rs;
		for (int ri = 0; ri < n; ++ri)
		{
			int r;
			scanf_s("%d", &r);
			rs.push_back(r);
		}
		
		std::vector<std::vector<int>> qs;
		for (int qi = 0; qi < n; ++qi)
		{
			qs.push_back(std::vector<int>());
			for (int qj = 0; qj < p; ++qj)
			{
				int q;
				scanf_s("%d", &q);
				qs[qi].push_back(q);
			}
		}

		int ans = calc(n, p, rs, qs);
		
		printf("Case #%d: %d\n", i, ans);
	}

	return 0;
}

struct line
{
public:
	line(int _min, int _max) : min(_min), max(_max), vec(_max-_min+1)
	{}

	const std::vector<int>& operator[](int index)
	{
		if (index >= min && index <= max)
		{
			return vec[index-min];
		}

		return std::vector<int>();
	}

	void push(int left, int right, int num)
	{
		for (int i = left; i <= right; ++i)
		{
			vec[i-min].push_back(num);
		}
	}

private:
	int min, max;
	std::vector<std::vector<int>> vec;
};

int calc(const int n, const int p, const std::vector<int>& rs, const std::vector<std::vector<int>> qs)
{
	std::vector<line> ls;

	int maxofmin = -1, minofmax = -1;

	for (int i = 0; i < n; ++i)
	{
		std::vector<std::pair<int, int>> servings;

		int min = -1, max = -1;
		for (int j = 0; j < p; ++j)
		{
			int low = static_cast<int>(std::ceil((double)qs[i][j]*10/11/rs[i]));
			int high = static_cast<int>(std::floor((double)qs[i][j]*10/9/rs[i]));

			if (high >= low)
			{
				servings.emplace_back(low, high);

				if (min == -1 || low < min) min = low;
				if (max == -1 || high > max) max = high;
			}
		}

		if (min == -1 || max == -1)
		{
			return 0;
		}

		ls.emplace_back(min, max);
		for (auto& p : servings)
		{
			ls[i].push(p.first, p.second, i);
		}

		if (maxofmin == -1 || min > maxofmin) maxofmin = min;
		if (minofmax == -1 || max < minofmax) minofmax = max;
	}
	
	for (int l = maxofmin; l <= minofmax; ++l)
	{
		for (int i = 0; i < n; ++i)
		{
		}
	}

	return 0;
}
