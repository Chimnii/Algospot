#include <iostream>

const int MAX_COUNT = 1000000007;

int dp[5001][101];

int calc( const int money, const int coinIndex, const int coinCount, const int coins[100] )
{
	if( money == 0 )
		return 1;

	if( dp[money][coinIndex] > 0 )
		return dp[money][coinIndex];

	for( int i=0; i<=coinIndex; ++i )
	{
		if( coins[i] <= money )
		{
			dp[money][coinIndex] += calc( money - coins[i], i, coinCount, coins );
			dp[money][coinIndex] %= MAX_COUNT;
		}
	}

	return dp[money][coinIndex];
}

int main( int argc, char** argv )
{
	int inputCount;

	std::cin >> inputCount;

	int coins[100];
	while( inputCount-- )
	{
		int money, coinCount;
		std::cin >> money >> coinCount;

		for( int i=0; i<coinCount; ++i )
			std::cin >> coins[i];

		for( int i=1; i<=money; ++i )
			for( int j=1; j<=coinCount; ++j )
				dp[i][j] = 0;

		int result = calc( money, coinCount-1, coinCount, coins );
		std::cout << result << std::endl;
	}
	
	return 0;
}