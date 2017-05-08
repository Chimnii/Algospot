#include <cstdio>

int main()
{
	FILE *fin, *fout;
	freopen_s(&fin, "CodeJam\\CruiseControl_in.txt", "r", stdin);
	freopen_s(&fout, "CodeJam\\CruiseControl_out.txt", "w", stdout);

	int t;
	scanf_s("%d", &t);

	for (int i = 1; i <= t; ++i)
	{
		int k, n;
		scanf_s("%d %d", &k, &n);

		double max_time = -1;
		for (int j = 0; j < n; ++j)
		{
			int kj, sj;
			scanf_s("%d %d", &kj, &sj);

			double time = static_cast<double>(k - kj) / sj;
			if (max_time == -1 || time > max_time)
			{
				max_time = time;
			}
		}

		printf("Case #%d: %.6f\n", i, static_cast<double>(k) / max_time);
	}

	return 0;
}
