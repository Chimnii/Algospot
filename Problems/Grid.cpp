#include <iostream>

int calc( int* dp, int n )
{
	if( n <= 1 )
		return 1;

	if( dp[n] > 0 )
		return dp[n];

	int i = n - 1;
	int result = 0;
	result += calc( dp, i-- ) * 1;
	result += calc( dp, i-- ) * 4;
	while( i >= 0 )
	{
		if( (n-i)%2 == 0 )
			result += calc( dp, i ) * 3;
		else
			result += calc( dp, i ) * 2;
		i--;
	}

	dp[n] = result;
	return result;
}

int main( int argc, char** argv )
{
	int testCase;
	std::cin >> testCase;

	for( int test = 1; test <= testCase; ++test )
	{
		int width;
		std::cin >> width;
		
		int* dp = new int[width+1];
		for( int i = 0; i <= width; ++i )
			dp[i] = 0;

		std::cout << test << " " << calc( dp, width ) << std::endl;

		delete[] dp;
		dp = NULL;
	}

	return 0;
}