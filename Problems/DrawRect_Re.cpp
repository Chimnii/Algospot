#include <stdio.h>

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
		int in_x, in_y;
		int answer_x = 0, answer_y = 0;
		for (int i = 0; i < 3; ++i)
		{
			scanf("%d %d\n", &in_x, &in_y);
			answer_x ^= in_x;
			answer_y ^= in_y;
		}

		printf("%d %d\n", answer_x, answer_y);
	}

	return 0;
}
