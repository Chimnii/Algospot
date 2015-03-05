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

enum e_board
{
	DOT = 0,
	X = 1,
	O = 2
};
enum e_result
{
	NONE = 0, // for caching
	LOSE,
	DRAW,
	WIN
};

e_board board[3][3];
e_result cached[19683];

e_result play( bool player );
int main( int argc, char** argv )
{
	int num_testcase;
	my::cin >> num_testcase;

	while( num_testcase-- )
	{
		memset( cached, 0, sizeof(cached) );

		int player = 0;
		for( int i = 0; i < 3; ++i )
		{
			for( int j = 0; j < 3; ++j )
			{
				char c;
				my::cin >> c;
				board[i][j] = ( c == '.' ? DOT : c == 'x' ? X : O );
				player += ( c == '.' ? 0 : c == 'x' ? 1 : -1 );
			}
		}
		
		e_result result = play( player <= 0 );
		switch(result)
		{
		case WIN: printf("x\n"); break;
		case LOSE: printf("o\n"); break;
		case DRAW: printf("TIE\n"); break;
		}
	}

	return 0;
}

int calc_cachier()
{
	int cachier = 0;
	for( int i = 0; i < 3; ++i )
	{
		for( int j = 0; j < 3; ++j )
		{
			cachier *= 3;
			cachier += board[i][j];
		}
	}

	return cachier;
}

e_result end_game()
{
	if( board[0][0] == X && board[0][1] == X && board[0][2] == X ) return WIN;
	if( board[1][0] == X && board[1][1] == X && board[1][2] == X ) return WIN;
	if( board[2][0] == X && board[2][1] == X && board[2][2] == X ) return WIN;
	if( board[0][0] == X && board[1][0] == X && board[2][0] == X ) return WIN;
	if( board[0][1] == X && board[1][1] == X && board[2][1] == X ) return WIN;
	if( board[0][2] == X && board[1][2] == X && board[2][2] == X ) return WIN;
	if( board[0][0] == X && board[1][1] == X && board[2][2] == X ) return WIN;
	if( board[0][2] == X && board[1][1] == X && board[2][0] == X ) return WIN;

	if( board[0][0] == O && board[0][1] == O && board[0][2] == O ) return LOSE;
	if( board[1][0] == O && board[1][1] == O && board[1][2] == O ) return LOSE;
	if( board[2][0] == O && board[2][1] == O && board[2][2] == O ) return LOSE;
	if( board[0][0] == O && board[1][0] == O && board[2][0] == O ) return LOSE;
	if( board[0][1] == O && board[1][1] == O && board[2][1] == O ) return LOSE;
	if( board[0][2] == O && board[1][2] == O && board[2][2] == O ) return LOSE;
	if( board[0][0] == O && board[1][1] == O && board[2][2] == O ) return LOSE;
	if( board[0][2] == O && board[1][1] == O && board[2][0] == O ) return LOSE;

	for( int i = 0; i < 3; ++i ) for( int j = 0; j < 3; ++j ) if( board[i][j] == DOT ) return NONE;

	return DRAW;
}

e_result play( bool player )
{
	e_result& result = cached[calc_cachier()];
	if( result != NONE )
	{
		return result;
	}

	result = end_game();
	if( result != NONE )
	{
		return result;
	}

	for( int i = 0; i < 3; ++i )
	{
		for( int j = 0; j < 3; ++j )
		{
			if( board[i][j] == DOT )
			{
				board[i][j] = player ? X : O;
				e_result next = play( !player );

				if( result == NONE || player && next > result || !player && next < result )
				{
					result = next;
				}
				board[i][j] = DOT;
			}
		}
	}

	return result;
}
