#include <stdio.h>

#ifdef __GNUC__
#define getchar getchar_unlocked
#endif

char input[8] = {0,};
int counts[8] = {0,};
int sums[8] = {0,};
int digits[8] = {10000000, 1000000, 100000, 10000, 1000, 100, 10, 1};

int main()
{
	char c, i, n;

	int number_count = 0;
	while( c = getchar(), c != '\n' )
		number_count = number_count * 10 + (c-'0');

	number_count = 1000000;
	for( int count = 0; count < number_count; ++count )
	{
		i = 7, n = 0;
		while( c = getchar(), c != '\n' )
			input[n++] = c;
		while( n-- )
		{
			sums[i] += input[n];
			++counts[i];
			--i;
		}
	}

	long long sum = 0;
	for( int i = 0; i < 8; ++i )
	{
		sum += (long long)digits[i] * (sums[i]-counts[i]*'0');
	}

	printf("%d\n", number_count);
	printf("%lld\n", sum);

	return 0;
}
