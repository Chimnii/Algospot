#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <functional>
#include <stdio.h>

struct road
{
	int s, d, g;
};

struct family
{
	int s, d;
};

int get_total_minimum_gas(int city, std::vector<road>& roads, std::vector<family>& families);

int main()
{
	int t;
	std::cin >> t;

	for (int i = 1; i <= t; ++i)
	{
		int n, m, k;
		std::cin >> n >> m >> k;

		std::vector<road> roads;
		while (m--)
		{
			road r;
			std::cin >> r.s >> r.d >> r.g;
			roads.emplace_back(r);
		}
		
		std::vector<family> families;
		while (k--)
		{
			family f;
			std::cin >> f.s >> f.d;
			families.emplace_back(f);
		}

		int answer = get_total_minimum_gas(n, roads, families);
		std::cout << "Case #" << i << ": " << answer << std::endl;
	}
	
	return 0;
}

std::vector<road> cities[101];
void init_cities(int city, std::vector<road>& roads)
{
	for (int i = 1; i <= city; ++i)
	{
		cities[i].clear();
	}

	for (const auto& road : roads)
	{
		auto r = road;

		cities[r.s].emplace_back(r);

		int tmp = r.s;
		r.s = r.d;
		r.d = tmp;
		cities[r.s].emplace_back(r);
	}
}

int minimum_gas[5001][5001];
void init_minimum_gas(std::vector<family>& families)
{
	family p, pp;
	p.s = p.d = pp.s = pp.d = 1;

	for (auto& f : families)
	{
		minimum_gas[pp.d][f.s] = -1;
		minimum_gas[p.s][f.s] = -1;
		minimum_gas[p.d][f.s] = -1;
		minimum_gas[p.d][f.d] = -1;
		minimum_gas[f.s][p.d] = -1;
		minimum_gas[f.s][f.d] = -1;

		pp = p;
		p = f;
	}
}

struct calcg
{
	int g, d;
	bool operator <(const calcg& other) const
	{
		return g < other.g;
	}
	bool operator >(const calcg& other) const
	{
		return g > other.g;
	}
};

int get_gas(int start, int dest)
{
	if (minimum_gas[start][dest] != -1)
	{
		return minimum_gas[start][dest];
	}

	std::priority_queue<calcg, std::vector<calcg>, std::greater<calcg>> queue;
	calcg cg;
	cg.d = start;
	cg.g = 0;
	queue.emplace(cg);

	bool visit[101] = {false,};
	while(queue.size() > 0)
	{
		calcg cg = queue.top();
		queue.pop();
		
		if (cg.d == dest)
		{
			minimum_gas[start][dest] = cg.g;
			minimum_gas[dest][start] = cg.g;
			return cg.g;
		}

		if (visit[cg.d])
		{
			continue;
		}
		visit[cg.d] = true;

		for (auto& r : cities[cg.d])
		{
			calcg ncg;
			ncg.d = r.d;
			ncg.g = cg.g + r.g;

			if (!visit[ncg.d])
			{
				queue.emplace(ncg);
			}
		}
	}

	return -1;
}

int get_total_minimum_gas(int city, std::vector<road>& roads, std::vector<family>& families)
{
	init_cities(city, roads);
	init_minimum_gas(families);

	// current_city, total_with_gas, total_without_gas;
	int cc = 1;
	int tw = 9999, two = 0;

	for (int f = 0; f < static_cast<int>(families.size()); ++f)
	{
		bool last_family = (f == static_cast<int>(families.size()) - 1);

		int ntwo = 0, ntw = 0;

		int ccfs = get_gas(cc, families[f].s);
		int fsfd = get_gas(families[f].s, families[f].d);
		int ccfd = get_gas(cc, families[f].d);
		if (ccfs == -1 || fsfd == -1)
		{
			return -1;
		}
			
		ntwo = std::min(two + ccfs + fsfd, tw + ccfd);

		if (!last_family)
		{
			int fsf1s = get_gas(families[f].s, families[f+1].s);
			int f1sfd = get_gas(families[f+1].s, families[f].d);
			int ccf1s = get_gas(cc, families[f+1].s);
			if (fsf1s == -1 || f1sfd == -1 || ccf1s == -1)
			{
				return -1;
			}

			ntw = std::min(two + ccfs + fsf1s + f1sfd, tw + ccf1s + f1sfd);
		}
		
		two = ntwo;
		tw = ntw;
		cc = families[f].d;
	}

	return two;
}
