#include <iostream>

const int T = 50;

const int N = 50;
const int M = 2;

const int Max = 100;

int main()
{
	printf("%d\n", T);

	for (int t = 0; t < T; ++t)
	{
		printf("%d %d\n", N, rand() % Max+1);

		for (int n = 0; n < N; ++n)
		{
			for (int m = 0; m < M; ++m)
			{
				printf("%d ", rand() % Max+1);
			}
			printf("\n");
		}
	}
	
	return 0;
}
