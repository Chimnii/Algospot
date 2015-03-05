#include <stdio.h>
#include <iostream>

namespace my
{
	struct istream{};
	istream cin;

	inline bool IsNum( char c ){ return ( c >= '0' && c <= '9' ); }
	inline istream& operator>>( istream& in, int& out )
	{
		char c; out = 0;
		while( c = getchar() ){ if( IsNum(c) ){ out += (c-'0'); break; } }
		while( c = getchar() ){ if( !IsNum(c) ) break; out *= 10; out += (c-'0'); }
		return in;
	}

	inline void calcMax( int& max, int value ){ if( max < value ) max = value; }
	inline void calcMin( int& min, int value ){ if( min > value ) min = value; }
}

int rows;
int triangle[101][101] = {0, };

int getPaths();
int main( int argc, char** argv )
{
	int numTestCase;
	my::cin >> numTestCase;

	while( numTestCase-- )
	{
		int sums[101][101] = {0,};
		int cnts[101][101] = {0,};

		my::cin >> rows;

		int n;
		for( int r = 1; r <= rows; ++r )
		{
			for( int c = 1; c <= r; ++c )
			{
				my::cin >> n;

				if( sums[r-1][c-1] > sums[r-1][c] )
				{
					sums[r][c] = sums[r-1][c-1] + n;
					cnts[r][c] = cnts[r-1][c-1];
				}
				else if( sums[r-1][c-1] < sums[r-1][c] )
				{
					sums[r][c] = sums[r-1][c] + n;
					cnts[r][c] = cnts[r-1][c];
				}
				else
				{
					sums[r][c] = sums[r-1][c] + n;
					cnts[r][c] = cnts[r-1][c-1] + cnts[r-1][c];
				}
				if( cnts[r][c] == 0 ) cnts[r][c] = 1;
			}
		}

		int sum = 0, cnt = 0;
		for( int c = 1; c <= rows; ++c )
		{
			if( sums[rows][c] > sum )
			{
				sum = sums[rows][c];
				cnt = cnts[rows][c];
			}
			else if( sums[rows][c] == sum )
			{
				cnt += cnts[rows][c];
			}
		}

		printf( "%d\n", cnt );
	}

	return 0;
}
