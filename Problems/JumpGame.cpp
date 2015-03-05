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

	inline int min( int a, int b ){ return a > b ? b : a; }
}

int boardSize;
int board[102][102] = {0,};

bool checkGame( int, int );
int main( int argc, char** argv )
{
	int numTestCase;
	my::cin >> numTestCase;

	while( numTestCase-- )
	{
		my::cin >> boardSize;
		for( int r = 1; r <= boardSize; ++r )
		{
			for( int c = 1; c <= boardSize; ++c )
			{
				my::cin >> board[r][c];
			}
		}

		if( checkGame( boardSize, boardSize ) )
			printf("YES\n");
		else
			printf("NO\n");
	}

	return 0;
}

bool checkGame( int row, int col )
{
	if( row == 1 && col == 1 )
	{
		return true;
	}

	int size = my::min( row - 1, 9 );
	for( int i = 1; i <= size; ++i )
	{
		if( board[row-i][col] == i )
		{
			board[row-i][col] = 0;
			if( checkGame( row - i, col ) )
				return true;
		}
	}

	size = my::min( col - 1, 9 );
	for( int i = 1; i <= size; ++i )
	{
		if( board[row][col-i] == i )
		{
			board[row][col-i] = 0;
			if( checkGame( row, col - i ) )
				return true;
		}
	}

	return false;
}