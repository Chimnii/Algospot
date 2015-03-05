#include <stdio.h>

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
}

const char DASH = 45;
const char DOT = 111;

int num_dash, num_dot, index;

int combination( int n, int m );
void print_indexed_morse( int remain_dash, int remain_dot, int remain_index );
int main( int argc, char** argv )
{
	int num_testcase;
	my::cin >> num_testcase;

	while( num_testcase-- )
	{
		my::cin >> num_dash >> num_dot >> index;
		print_indexed_morse( num_dash, num_dot, index );
		printf("\n");
	}

	return 0;
}

void print_indexed_morse( int remain_dash, int remain_dot, int remain_index )
{
	if( remain_dash <= 0 && remain_dot <= 0 )
	{
		return;
	}
	else if( remain_dot <= 0 )
	{
		printf( "%c", DASH );
		print_indexed_morse( remain_dash-1, remain_dot, remain_index );
		return;
	}
	else if( remain_dash <= 0 )
	{
		printf( "%c", DOT );
		print_indexed_morse( remain_dash, remain_dot-1, remain_index );
		return;
	}

	int comb = combination( remain_dash + remain_dot - 1, remain_dash - 1 );
	if( remain_index <= comb )
	{
		printf( "%c", DASH );
		print_indexed_morse( remain_dash-1, remain_dot, remain_index );
	}
	else
	{
		printf( "%c", DOT );
		print_indexed_morse( remain_dash, remain_dot-1, remain_index - comb );
	}
}

int cached[201][101] = {0,};
int combination( int n, int r )
{
	int& value = cached[n][r];
	if( value > 0 )
	{
		return value;
	}

	if( n == r || r == 0 )
	{
		value = 1;
	}
	else if( r == 1 )
	{
		value = n;
	}
	else
	{
		value = combination( n-1, r-1 ) + combination( n-1, r );
		if( value > 1000000001 )
			value = 1000000001;
	}

	return value;
}