#include <cstdio>
#include <vector>
#include <algorithm>

enum ework
{
	none = 0,
	cameron = 1,
	james = 2,
	cameron_space = 3,
	james_space = 4,
	common_space = 5,
};

constexpr int maxsize = 1440;
int works[maxsize];

void incr(int& index)
{
	index = (index + 1) % maxsize;
}
void decr(int& index)
{
	index = (index + maxsize - 1) % maxsize;
}

struct range
{
	int b, e, w;
	range() : b(0), e(0), w(0) {}
	range(int _b, int _e, int _w) : b(_b), e(_e), w(_w) {}
};
bool leftmost(const range& a, const range& b)
{
	return a.b < b.b;
}
bool shortmost(const range& a, const range& b)
{
	return (a.e - a.b) < (b.e - b.b);
}

std::vector<range> ranges;

int main()
{
	FILE *fin, *fout;
	freopen_s(&fin, "CodeJam\\ParentingPartnering_in.txt", "r", stdin);
	freopen_s(&fout, "CodeJam\\ParentingPartnering_out.txt", "w", stdout);

	int t;
	scanf_s("%d", &t);

	for (int i = 1; i <= t; ++i)
	{
		int nc, nj;
		scanf_s("%d %d", &nc, &nj);


		int sum_james = 0, sum_cameron = 0;
		ranges.clear();

		for (int nci = 0; nci < nc; ++nci)
		{
			int b, e;
			scanf_s("%d %d", &b, &e);

			sum_james += e-b;
			ranges.emplace_back(b, e, james);
		}
		for (int nji = 0; nji < nj; ++nji)
		{
			int b, e;
			scanf_s("%d %d", &b, &e);
			
			sum_cameron += e-b;
			ranges.emplace_back(b, e, cameron);
		}

		std::vector<range> none_ranges;
		std::sort(ranges.begin(), ranges.end(), leftmost);
		for (int i = 0; i < ranges.size(); ++i)
		{
			int p, n;
			if (i == 0) { p = ranges.size() - 1; n = 0; }
			else { p = i-1; n = i; }

			int w;
			if (ranges[p].w == ranges[n].w == cameron) w = cameron_space;
			if (ranges[p].w == ranges[n].w == james) w = james_space;
			if (ranges[p].w != ranges[n].w) w = common_space;

			none_ranges.emplace_back(ranges[p].e, ranges[n].b, w);
		}
		ranges.insert(ranges.end(), none_ranges.begin(), none_ranges.end());

		// calc
		std::sort(ranges.begin(), ranges.end(), leftmost);
		while (true)
		{
			range shortr(0, maxsize, none);
			for (auto& r : ranges)
			{
				if (r.e - r.b <= shortr.e - shortr.b)
				{

				}
			}
		}
		
		// output
		printf("Case #%d: %d\n", i, 0);
	}

	return 0;
}
