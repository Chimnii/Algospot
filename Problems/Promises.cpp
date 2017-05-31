#include <iostream>
#include <vector>
#include <algorithm>

using std::pair;
using std::vector;

constexpr int maxsize = 200;
constexpr int maxvalue = 100000 * 200 * 10;

void precalc(const int num_city);
bool is_need(const int num_city, const int start, const int finish, const int distance);
int dist[maxsize][maxsize];

int main()
{
#ifdef FILEINPUT
	freopen("input.txt", "r", stdin);
#endif
	std::ios::sync_with_stdio(false);

	int num_testcase;
	std::cin >> num_testcase;
	
	while (num_testcase--)
	{
		int num_city, num_road, num_newroad;
		std::cin >> num_city >> num_road >> num_newroad;
		
		for (int i = 0; i < num_city; ++i)
		{
			for(int j = 0; j < num_city; ++j)
			{
				dist[i][j] = (i == j) ? 0 : maxvalue;
			}
		}

		for (int i = 0; i < num_road; ++i)
		{
			int s, f, d;
			std::cin >> s >> f >> d;
			dist[s][f] = d;
			dist[f][s] = d;
		}

		precalc(num_city);

		int result = 0;
		for (int i = 0; i < num_newroad; ++i)
		{
			int s, f, d;
			std::cin >> s >> f >> d;
			if (!is_need(num_city, s, f, d))
			{
				++result;
			}
		}
		std::cout << result << "\n";
	}

	return 0;
}

void precalc(const int num_city)
{
	for (int k = 0; k < num_city; ++k)
	{
		for (int i = 0; i < num_city; ++i)
		{
			if (dist[i][k] == maxvalue || i == k) continue;

			for (int j = 0; j < num_city; ++j)
			{
				if (i == j) continue;

				dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}
}

bool is_need(const int num_city, const int start, const int finish, const int distance)
{
	if (dist[start][finish] <= distance)
	{
		return false;
	}

	for (int i = 0; i < num_city; ++i)
	{
		for (int j = 0; j < num_city; ++j)
		{
			dist[i][j] = std::min(dist[i][j],
				std::min(dist[i][start] + dist[finish][j] + distance, dist[i][finish] + dist[start][j] + distance));
		}
	}

	return true;
}
