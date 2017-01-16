#include <iostream>
#include <vector>
#include <limits>

std::vector<int> costs[301];

int calc_minimum_cost(const int n, const int m);

int main()
{
	int t;
	scanf_s("%d", &t);

	for (int i = 1; i <= t; ++i)
	{
		int n, m;
		scanf_s("%d %d", &n, &m);

		for (int j = 0; j < n; ++j)
		{
			costs[j].clear();
			for (int k = 0; k < m; ++k)
			{
				int cost;
				scanf_s("%d", &cost);

				costs[j].push_back(cost);
			}
		}

		int boughts[301] = {0,};
		for (int day = 0; day < n; ++day)
		{
			boughts[day] = 0;
		}

		int total_cost = 0;
		for (int day = 1; day <= n; ++day)
		{
			int min_j, min_k, min_cost;
			min_j = min_k = min_cost = std::numeric_limits<int>::max();

			for (int j = 0; j < day; ++j)
			{
				int count = static_cast<int>(costs[j].size());
				for (int k = 0; k < count; ++k)
				{
					int cost = costs[j][k] + std::pow(boughts[j]+1, 2) - std::pow(boughts[j], 2);
					if (cost < min_cost)
					{
						min_cost = cost;
						min_j = j;
						min_k = k;
					}
				}
			}

			costs[min_j].erase(costs[min_j].begin() + min_k);
			++boughts[min_j];
			total_cost += min_cost;
		}

		printf("Case #%d: %d\n", i, total_cost);
	}

	return 0;
}

int calc_minimum_cost(const int n, const int m)
{
	return n;
}
