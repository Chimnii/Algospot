#include <cstdio>
#include <vector>
#include <queue>
#include <functional>

using std::pair;
using std::make_pair;
using std::vector;
using std::priority_queue;

int calc_minimum_distance(const vector<pair<bool, vector<pair<int, int>>>>& spots, const int begin);
int main()
{
#ifdef FILEINPUT
	FILE* fin;
	freopen_s(&fin, "input.txt", "r", stdin);
#endif

	int num_testcase;
	scanf("%d\n", &num_testcase);

	while (num_testcase--)
	{
		int num_spot, num_road, num_firedspot, num_firestation;
		scanf("%d %d %d %d\n", &num_spot, &num_road, &num_firedspot, &num_firestation);

		vector<pair<bool, vector<pair<int, int>>>> spots(num_spot + 1, make_pair(false, vector<pair<int, int>>()));
		for (int i = 0; i < num_road; ++i)
		{
			int s, e, d;
			scanf("%d %d %d", &s, &e, &d);
			spots[s].second.emplace_back(make_pair(d, e));
			spots[e].second.emplace_back(make_pair(d, s));
		}
		vector<int> firedspots;
		for (int i = 0; i < num_firedspot; ++i)
		{
			int spot;
			scanf("%d", &spot);
			firedspots.emplace_back(spot);
		}
		for (int i = 0; i < num_firestation; ++i)
		{
			int station;
			scanf("%d", &station);
			spots[station].first = true;
		}

		int total_dist = 0;
		for (int fs : firedspots)
		{
			total_dist += calc_minimum_distance(spots, fs);
		}
		printf("%d\n", total_dist);
	}

	return 0;
}

int calc_minimum_distance(const vector<pair<bool, vector<pair<int, int>>>>& spots, const int begin)
{
	vector<int> dists(spots.size(), -1);

	priority_queue<pair<int, int>, vector<pair<int, int>>, std::greater<pair<int, int>>> road_queue;
	road_queue.emplace(make_pair(0, begin));
	dists[begin] = 0;

	while (!road_queue.empty())
	{
		auto current = road_queue.top();
		road_queue.pop();
		int current_dist = current.first;
		int current_spot = current.second;

		if (current_dist > dists[current_spot])
			continue;

		if (spots[current_spot].first)
			return dists[current_spot];

		for (auto& road : spots[current_spot].second)
		{
			int next_dist = current_dist + road.first;
			int next_spot = road.second;
			if (dists[next_spot] == -1 || next_dist < dists[next_spot])
			{
				dists[next_spot] = next_dist;
				road_queue.emplace(make_pair(next_dist, next_spot));
			}
		}
	}

	return -1;
}