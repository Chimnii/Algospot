#include <stdio.h>
#include <string.h>

namespace my
{
	struct istream{};
	istream cin;

	inline bool is_num( char c ){ return ( c >= '0' && c <= '9' ); }
	inline bool is_negative( char c ){ return c == '-'; }
	inline istream& operator>>( istream& in, int& out )
	{
		char c; out = 0; bool neg = false;
		while( c = getchar() ){ if( is_negative(c) ){ neg = true; break; } if( is_num(c) ){ out += (c-'0'); break; } }
		while( c = getchar() ){ if( !is_num(c) ) break; out *= 10; out += (c-'0'); }
		if( neg ) out *= -1;
		return in;
	}

	inline bool is_char( char c ){ return ( c > ' '  ); }
	inline istream& operator>>( istream& in, char& out )
	{
		char c;
		while( c = getchar() ){ if( is_char(c) ){ out = c; break; } }
		return in;
	}
}

typedef char e_result;
const char NONE = 0, WIN = 1, LOSE = 2;
char cached[33554433];

bool board[7][7];

e_result play( bool player );
int main( int argc, char** argv )
{
	for( int i = 0; i < 7; ++i ) for( int j = 0; j < 7; ++j ) board[i][j] = true;

	int num_testcase;
	my::cin >> num_testcase;

	while( num_testcase-- )
	{
		memset( cached, 0, sizeof(cached) );

		for( int i = 1; i <= 5; ++i )
		{
			for( int j = 1; j <= 5; ++j )
			{
				char c;
				my::cin >> c;
				board[i][j] = ( c == '.' ? false : true );
			}
		}

		e_result result = play(true);
		printf( result == WIN ? "WINNING\n" : "LOSING\n" );
	}

	return 0;
}

int calc_cachier()
{
	int cachier = 0;
	for( int i = 1; i <= 5; ++i )
	{
		for( int j = 1; j <= 5; ++j )
		{
			cachier = cachier << 1;

			if( board[i][j] == true || ( board[i-1][j] == true && board[i+1][j] == true && board[i][j-1] == true && board[i][j+1] == true ) )
				cachier += 1;
		}
	}

	return cachier;
}

bool put( bool player, e_result& next, int i, int j, int i1, int j1, int i2, int j2 )
{
	if( board[i1][j1] == false && board[i2][j2] == false )
	{
		board[i][j] = board[i1][j1] = board[i2][j2] = true;

		next = play( !player );

		board[i][j] = board[i1][j1] = board[i2][j2] = false;

		return true;
	}

	return false;
}

e_result play( bool player )
{
	e_result& result = cached[calc_cachier()];
	if( result != NONE )
	{
		return result;
	}

	e_result next;
	result = WIN;
	for( int i = 1; i <= 5; ++i )
	{
		for( int j = 1; j <= 5; ++j )
		{
			if( board[i][j] == false )
			{
				if( put( player, next, i, j, i-1, j, i, j-1 ) && next == LOSE ) return result;
				if( put( player, next, i, j, i-1, j, i, j+1 ) && next == LOSE ) return result;
				if( put( player, next, i, j, i+1, j, i, j-1 ) && next == LOSE ) return result;
				if( put( player, next, i, j, i+1, j, i, j+1 ) && next == LOSE ) return result;
				if( put( player, next, i, j, i+1, j, i+1, j ) && next == LOSE ) return result;
				if( put( player, next, i, j, i, j+1, i, j+1 ) && next == LOSE ) return result;
			}
		}
	}

	result = LOSE;
	return result;
}
