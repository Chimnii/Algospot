#include <stdio.h>
#include <vector>
#include <map>
#include <algorithm>

using std::vector;
using std::sort;
using std::map;
using std::pair;
using std::make_pair;

static constexpr int num_mod = 1000000007;

vector<int> coin_costs;
map<pair<int, int>, int> memo;
int find_combination( int remain_cost, int coin_index )
{
	if (remain_cost < 0) return 0;
	if (remain_cost == 0) return 1;

	auto it = memo.find( make_pair( remain_cost, coin_index ) );
	if (it != memo.end())
		return it->second;

	int comb = 0;
	for (size_t i = coin_index; i < coin_costs.size(); ++i)
	{
		comb = (comb + find_combination( remain_cost - coin_costs[i], i )) % num_mod;
	}

	memo.emplace( make_pair( remain_cost, coin_index ), comb );
	return comb;
}

int main()
{
#ifdef FILEINPUT
	FILE* fin;
	freopen_s(&fin, "input.txt", "r", stdin);
#endif
	int num_testcase;
	scanf("%d\n", &num_testcase);

	while(num_testcase--)
	{
		memo.clear();
		coin_costs.clear();

		int total_cost, num_coin;
		scanf("%d %d\n", &total_cost, &num_coin);

		for (int i = 0; i < num_coin; ++i)
		{
			int cost;
			scanf("%d", &cost);
			coin_costs.emplace_back(cost);
		}

		sort(coin_costs.begin(), coin_costs.end(), [](const int& i1, const int& i2) -> bool { return i1 > i2; });

		int count_combination = find_combination( total_cost, 0 );
		printf("%d\n", count_combination);
	}

	return 0;
}
