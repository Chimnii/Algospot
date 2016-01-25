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
}

const int size = 1 << 23;
int buffer[size];

int main( int argc, char** argv )
{
	int num_testcase;
	my::cin >> num_testcase;

	while( num_testcase-- )
	{
		int subsum, num_seq;
		my::cin >> subsum >> num_seq;

		int count = 0;

		int begin = 0, end = 0;
		int begin_index = 0, end_index = 0;

		long long sign = 1983;
		long long current_sum = 0;
		while( end <= num_seq )
		{
			if( current_sum == subsum )
				++count;

			if( current_sum <= subsum )
			{
				int current = sign % 10000 + 1;
				buffer[end_index] = current;
				current_sum += current;

				sign = (sign * 214013 + 2531011) % 4294967296LL;
				++end;
				if( ++end_index == size )
					end_index = 0;
			}
			else
			{
				current_sum -= buffer[begin_index];

				++begin;
				if( ++begin_index == size )
					begin_index = 0;
			}
		}

		printf("%d\n", count);
	}

	return 0;
}

/*
100
8791 20
5265 5000
3578452 5000000
3578452 50000000
*/