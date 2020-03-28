#include <stdio.h>

static constexpr int count_of_building = 9;

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
		int sum;
		scanf("%d\n", &sum);

		int used;
		for (int i = 0; i < count_of_building; ++i)
		{
			scanf("%d", &used);
			sum -= used;
		}

		printf( sum >= 0 ? "YES\n" : "NO\n" );
	}

	return 0;
}
