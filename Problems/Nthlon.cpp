#include <cstdio>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <limits>

using std::pair;
using std::vector;
using std::priority_queue;
using std::unordered_map;
using game = pair<int, int>;
using sumdiff = pair<int, int>;

const int max_minutes = 200;

bool compare_game(const game& g1, const game& g2)
{
	return std::max(g1.first, g1.second) < std::max(g2.first, g2.second);
}

int calc_minimum_minute(const vector<game>& games);
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
		int num_game;
		scanf("%d\n", &num_game);

		int left = 0, same = 0, right = 0;
		vector<game> temp_games(max_minutes * 2, std::make_pair(-1, -1));
		for (int i = 0; i < num_game; ++i)
		{
			int a, b;
			scanf("%d %d", &a, &b);
			
			int index = a + max_minutes - b;
			if (temp_games[index].first == -1 || temp_games[index].first > a)
			{
				temp_games[index].first = a;
				temp_games[index].second = b;

				if (index < max_minutes) ++right;
				else if (index == max_minutes) ++same;
				else ++left;
			}
		}

		if (same == 0 && left * right == 0)
		{
			printf("IMPOSSIBLE\n");
			continue;
		}

		vector<game> games;
		for (auto& g : temp_games)
		{
			if (g.first != -1)
				games.emplace_back(g);
		}

		std::sort(games.begin(), games.end(), compare_game);

		int min = calc_minimum_minute(games);
		printf("%d\n", min);
	}

	return 0;
}

game make_game(const sumdiff& sd)
{
	if (sd.second == 0) return std::make_pair(sd.first, sd.first);
	else if(sd.second > 0) return std::make_pair(sd.first, sd.first - sd.second);
	else return std::make_pair(sd.first + sd.second, sd.first);
}

int calc_minimum_minute(const vector<game>& games)
{
	unordered_map<int, int> map;

	priority_queue<pair<int, int>, vector<pair<int, int>>, std::greater<pair<int, int>>> queue;
	queue.emplace(0, 0);
	map[0] = std::numeric_limits<int>::max();
	
	while (!queue.empty())
	{
		auto current = queue.top();
		int current_sum = current.first;
		int current_diff = current.second;
		queue.pop();

		if (current_diff == 0 && current_sum != 0)
			return current_sum;

		if (current_sum > map[current_diff])
			continue;

		for (auto& g : games)
		{
			game sum_game = make_game(current);
			sum_game.first += g.first;
			sum_game.second += g.second;
			int next_sum = std::max(sum_game.first, sum_game.second);
			int next_diff = sum_game.first - sum_game.second;
			
			auto it = map.find(next_diff);
			if (it == map.end() || it->second > next_sum)
			{
				map[next_diff] = next_sum;
				queue.emplace(next_sum, next_diff);
			}
		}
	}

	return -1;
}
