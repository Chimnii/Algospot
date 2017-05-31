#include <iostream>
#include <vector>
#include <algorithm>

using std::pair;
using std::vector;

constexpr int maxvalue = 500 * 100 * 10;

void calc_times(const vector<pair<int, int>>& ordered_places, const vector<vector<int>>& roads, vector<vector<int>>& times);
int main()
{
#ifdef FILEINPUT
	freopen("input.txt", "r", stdin);
#endif
	std::ios::sync_with_stdio(false);

	int num_place, num_road;
	std::cin >> num_place >> num_road;

	vector<pair<int, int>> ordered_places;
	for (int i = 0; i < num_place; ++i)
	{
		int time;
		std::cin >> time;
		ordered_places.emplace_back(time, i);
	}
	std::sort(ordered_places.begin(), ordered_places.end());

	vector<vector<int>> roads(num_place, vector<int>(num_place, maxvalue));
	for (int i = 0; i < num_road; ++i)
	{
		int s, f, d;
		std::cin >> s >> f >> d;
		--s, --f;
		if (roads[s][f] >= d)
		{
			roads[s][f] = d;
			roads[f][s] = d;
		}
	}

	vector<vector<int>> times(num_place, vector<int>(num_place, maxvalue));
	calc_times(ordered_places, roads, times);

	int num_testcase;
	std::cin >> num_testcase;
	while (num_testcase--)
	{
		int s, f;
		std::cin >> s >> f;
		--s, --f;
		std::cout << times[s][f] << "\n";
	}

	return 0;
}

void calc_times(const vector<pair<int, int>>& ordered_places, const vector<vector<int>>& roads, vector<vector<int>>& times)
{
	int size = static_cast<int>(ordered_places.size());

	times = roads;
	vector<vector<int>> noinspect_times(roads);

	for (int i = 0; i < size; ++i)
	{
		times[i][i] = noinspect_times[i][i] = 0;
	}

	for (auto op : ordered_places)
	{
		int inspect_time = op.first;
		int p = op.second;

		for (int i = 0; i < size; ++i)
		{
			if (noinspect_times[i][p] == maxvalue || i == p)
				continue;

			for (int j = 0; j < size; ++j)
			{
				if (j == p)
					continue;
				noinspect_times[i][j] = (i == j) ? 0 : std::min(noinspect_times[i][j], noinspect_times[i][p] + noinspect_times[p][j]);
				times[i][j] = (i == j) ? 0 : std::min(times[i][j], noinspect_times[i][p] + noinspect_times[p][j] + op.first);
			}
		}
	}
}