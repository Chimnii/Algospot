#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>

struct pie
{
	int r, h;
	pie(int _r, int _h) : r(_r), h(_h) {}

	bool operator ==(const pie& other) const
	{
		return (r == other.r && h == other.h);
	}
};

const double pi = std::atan(1) * 4;

int main()
{
	FILE *fin, *fout;
	freopen_s(&fin, "CodeJam\\AmpleSyrup_in.txt", "r", stdin);
	freopen_s(&fout, "CodeJam\\AmpleSyrup_out.txt", "w", stdout);

	int t;
	scanf_s("%d", &t);

	for (int i = 1; i <= t; ++i)
	{
		int n, k;
		scanf_s("%d %d", &n, &k);

		std::vector<pie> pies;
		for (int ni = 0; ni < n; ++ni)
		{
			int r, h;
			scanf_s("%d %d", &r, &h);
			pies.emplace_back(r, h);
		}

		int maxr = 0;
		long long sum = 0;
		while (k--)
		{
			long long max_increased = 0;
			std::vector<pie>::iterator maxp;

			for (auto& it = pies.begin(); it != pies.end(); ++it)
			{
				auto& p = *it;
				long long increased = 0;
				if (maxr == 0)
				{
					increased = static_cast<long long>(p.r) * p.r + 2 * p.r * p.h;
				}
				else if (p.r > maxr)
				{
					increased = static_cast<long long>(p.r) * p.r - maxr * maxr + 2 * p.r * p.h;
				}
				else
				{
					increased = static_cast<long long>(2) * p.r * p.h;
				}

				if (increased > max_increased)
				{
					max_increased = increased;
					maxp = it;
				}
			}

			sum += max_increased;
			if (maxp->r >= maxr)
			{
				maxr = maxp->r;
			}

			pies.erase(maxp);
		}

		printf("Case #%d: %.9f\n", i, pi*sum);
	}

	return 0;
}
