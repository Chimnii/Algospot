#include <iostream>
#include <vector>
#include <limits>

using std::pair;
using std::vector;

constexpr int ourgalaxy = 0;
constexpr int andromedagalaxy = 1;
constexpr int maxdistance = 1000 * 100 * 100 * 3;
constexpr int mindistance = -1000 * 100 * 100 * 3;
constexpr int pinfinity = maxdistance * 10;
constexpr int ninfinity = mindistance * 10;


enum class eresult { unreachable, infinite, reachable };
using holes = vector<pair<int, int>>;

pair<eresult, eresult> calc_distance(const vector<holes>& galaxies, vector<int>& upper, vector<int>& lower);
int main()
{
#ifdef FILEINPUT
	freopen("input.txt", "r", stdin);
#endif
	std::ios_base::sync_with_stdio(false);

	int num_testcase;
	std::cin >> num_testcase;

	while (num_testcase--)
	{
		int num_galaxy, num_wormhole;
		std::cin >> num_galaxy >> num_wormhole;

		vector<holes> galaxies(num_galaxy);
		for (int i = 0; i < num_wormhole; ++i)
		{
			int s, f, d;
			std::cin >> s >> f >> d;
			galaxies[s].emplace_back(f, d);
		}

		vector<int> upper(num_galaxy, pinfinity);
		vector<int> lower(num_galaxy, ninfinity);
		auto result = calc_distance(galaxies, upper, lower);
		if (result.first == eresult::unreachable)
		{
			std::cout << "UNREACHABLE\n";
		}
		else
		{
			if (result.first == eresult::infinite) std::cout << "INFINITY";
			else std::cout << upper[andromedagalaxy];
			std::cout << " ";

			if (result.second == eresult::infinite) std::cout << "INFINITY";
			else std::cout << lower[andromedagalaxy];
			std::cout << "\n";
		}
	}
}

bool update(const vector<holes>& galaxies, vector<int>& upper, vector<int>& lower)
{
	int size = static_cast<int>(galaxies.size());

	bool updated = true;
	for (int v = 0; v < size && updated; ++v)
	{
		updated = false;
		for (int g = 0; g < size; ++g)
		{
			for (auto& hole : galaxies[g])
			{
				int next_g = hole.first;
				int next_upper_dist = upper[g] + hole.second;
				if (next_upper_dist < upper[next_g])
				{
					upper[next_g] = next_upper_dist;
					updated = true;
				}

				int next_lower_dist = lower[g] + hole.second;
				if (next_lower_dist > lower[next_g])
				{
					lower[next_g] = next_lower_dist;
					updated = true;
				}
			}
		}
	}

	return updated;
}

pair<eresult, eresult> calc_distance(const vector<holes>& galaxies, vector<int>& upper, vector<int>& lower)
{
	int size = static_cast<int>(galaxies.size());

	upper[ourgalaxy] = 0;
	lower[ourgalaxy] = 0;

	eresult upper_result = eresult::unreachable;
	eresult lower_result = eresult::unreachable;

	bool updated = update(galaxies, upper, lower);
	if (upper[andromedagalaxy] > maxdistance || lower[andromedagalaxy] < mindistance)
	{
		return std::make_pair(upper_result, lower_result);
	}

	if (updated)
	{
		auto current_upper = upper[andromedagalaxy];
		auto current_lower = lower[andromedagalaxy];
		update(galaxies, upper, lower);

		if (current_upper != upper[andromedagalaxy]) upper_result = eresult::infinite;
		if (current_lower != lower[andromedagalaxy]) lower_result = eresult::infinite;
	}

	if (upper_result != eresult::infinite) upper_result = eresult::reachable;
	if (lower_result != eresult::infinite) lower_result = eresult::reachable;
	return std::make_pair(upper_result, lower_result);
}

