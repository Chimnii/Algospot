#include <stdio.h>

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

	inline int max( int a, int b ){ return a > b ? a : b; }
	inline void calcMax( int& max, int value ){ if( max < value ) max = value; }
}

int main( int argc, char** argv )
{
	int numTestCase;
	my::cin >> numTestCase;

	while( numTestCase-- )
	{
		int size;
		my::cin >> size;

		int n;
		int board[101][101] = {0,};
		for( int r = 1; r <= size-1; ++r )
		{
			for( int c = 1; c <= r; ++c )
			{
				my::cin >> n;
				board[r][c] = my::max( board[r-1][c-1], board[r-1][c] ) + n;
			}
		}

		int maxSum = 0;
		for( int c = 1; c <= size; ++ c )
		{
			my::cin >> n;
			board[size][c] = my::max( board[size-1][c-1], board[size-1][c] ) + n;
			my::calcMax( maxSum, board[size][c] );
		}

		printf( "%d\n", maxSum );
	}

	return 0;
}
