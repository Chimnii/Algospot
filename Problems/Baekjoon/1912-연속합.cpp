#include <stdio.h>
#include <limits>

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

	inline void calc_max( int& max, int value ){ if( max < value ) max = value; }
	inline void calc_min( int& min, int value ){ if( min > value ) min = value; }
}

int main( int argc, char** argv )
{
	int N;
	my::cin >> N;

	int curr_max = std::numeric_limits<int>::min();
	int curr_min = 0;
	int temp_min = 0;

	int n, accum = 0;
	for( int i = 0; i < N; ++i )
	{
		my::cin >> n;
		accum += n;

		if( accum > curr_max )
		{
			curr_max = accum;
		}

		if( accum - temp_min > curr_max - curr_min )
		{
			curr_max = accum;
			curr_min = temp_min;
			temp_min = 0;
		}

		if( accum < temp_min )
		{
			temp_min = accum;
		}
	}

	printf("%d\n", curr_max-curr_min);

	return 0;
}
