#include <iostream>

long long hanoi3[1024];
long long hanoi4[1024];

int main()
{
	std::ios::sync_with_stdio(false);

	hanoi3[1] = 1;
	for (int i = 2; i <= 1000; ++i)
	{
		hanoi3[i] = 2 * hanoi3[i-1] + 1;
	}

	hanoi4[1] = 1;
	for (int i = 2; i <= 1000; ++i)
	{
		long long min = -1;
		for (int j = i-1; j >= 1 && hanoi4[j] >= hanoi3[i-j-1]; --j)
		{
			long long sum = hanoi4[j] * 2 + hanoi3[i-j-1] * 2 + 1;
			if (min == -1 || min > sum)
				min = sum;
		}
		hanoi4[i] = min;
	}

	int i = 1;
	int n;
	while (std::cin >> n)
	{
		std::cout << "Case " << i << ": " << hanoi4[n];
		++i;

#ifdef TEST
		for (int j = n-1; j >= 1 && hanoi4[j] >= hanoi3[n-j-1]; --j)
		{
			long long sum = hanoi4[j] * 2 + hanoi3[n-j-1] * 2 + 1;
			if (sum == hanoi4[n])
				std::cout << "(" << j << ", " << n-j-1 << ") ";
		}
#endif
		std::cout << "\n";
	}
	
	return 0;
}
