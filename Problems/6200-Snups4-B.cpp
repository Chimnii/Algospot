// unsolved
#include <iostream>
#include <string>
#include <cmath>

const int max_comb = 65;
long long comb[max_comb+1][max_comb+1];

void set_comb();
std::string get_binary( int n );
long long get_round( int length, int c0, int c1 );
int main()
{
	set_comb();

	long long count;
	int start, finish;
	while( std::cin >> start >> finish )
	{
		count = 0;

		std::string bstart = get_binary(start);
		std::string bfinish = get_binary(finish);

		// TODO bstart.lenght == bfinish.length
		// TODO get_round Æ²¸²

		int c0, c1, length;

		c0 = 0, c1 = 1, length = bstart.length();
		for( int i = 1; i < length; ++i )
		{
			if( bstart[i] == '0' )
			{
				count += get_round( length, c0, c1+1 );
				++c0;
			}
			else
			{
				++c1;
			}
		}
		count += get_round( length, c0, c1 );

		c0 = 0, c1 = 1, length = bfinish.length();
		for( int i = 1; i < length; ++i )
		{
			if( bfinish[i] == '0' )
			{
				++c0;
			}
			else
			{
				count += get_round( length, c0+1, c1 );
				++c1;
			}
		}
		count += get_round( length, c0, c1 );

		for( int i = bstart.length()+1; i < bfinish.length(); ++i )
		{
			count += get_round( i, 0, 1 );
		}

		std::cout << count << std::endl;
	}
	
	return 0;
}

void set_comb()
{
	for( int i = 1; i <= max_comb; ++i )
	{
		comb[i][0] = 1;
		comb[i][i] = 1;
	}
	for( int i = 2; i <= max_comb; ++i )
	{
		for( int j = 1; j < i; ++j )
		{
			comb[i][j] = comb[i-1][j-1] + comb[i-1][j];
		}
	}
}

std::string get_binary( int n )
{
	if( n == 0 ) return "0";
	else if( n == 1 ) return "1";

	return get_binary(n/2) + (n%2 ? '1' : '0');
}

long long get_round( int length, int c0, int c1 )
{
	if( length == c0 + c1 )
		return c0 >= c1 ? 1 : 0;

	long long count = 0;

	int n = length - c0 - c1;
	int r = (n - std::abs((c1-c0)) + 1) / 2 + c0;
	while( r <= n )
		count += comb[n][r++];

	return count;
}
