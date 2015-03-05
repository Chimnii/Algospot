#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cmath>

namespace my
{
	struct istream{};
	istream cin;

	inline bool IsNum( char c ){ return ( c >= '0' && c <= '9' ); }
	inline bool IsNegative( char c ){ return c == '-'; }
	inline istream& operator>>( istream& in, int& out )
	{
		char c; out = 0; bool neg = false;
		while( c = getchar() ){ if( IsNegative(c) ){ neg = true; break; } if( IsNum(c) ){ out += (c-'0'); break; } }
		while( c = getchar() ){ if( !IsNum(c) ) break; out *= 10; out += (c-'0'); }
		if( neg ) out *= -1;
		return in;
	}
}

int length, count;
int seq[101], sum[101], square_sum[101];
int dp[101][101][11][2];

int quantize( int begin, int end, int remain_count );
int sectionQuantize( int begin, int end );
int main( int argc, char** argv )
{
	int numTestCase;
	my::cin >> numTestCase;

	while( numTestCase-- )
	{
		int length, count;
		my::cin >> length >> count;

		for( int i = 0; i < length; ++i )
		{
			my::cin >> seq[i];
		}
		std::sort( &seq[0], &seq[length] );

		int curr_sum = 0;
		int curr_square_sum = 0;
		for( int i = 0; i < length; ++i )
		{
			curr_sum += seq[i];
			sum[i] = curr_sum;

			curr_square_sum += seq[i] * seq[i];
			square_sum[i] = curr_square_sum;
		}

		memset( dp, 0, sizeof(dp) );

		printf( "%d\n", quantize( 0, length, count ) );
	}

	return 0;
}

int quantize( int begin, int end, int remain_count )
{
	int& value = dp[begin][end][remain_count][0];
	int& checked = dp[begin][end][remain_count][1];

	if( checked > 0 )
		return value;

	if( remain_count == 1 )
	{
		value = sectionQuantize( begin, end );
		checked = 1;
		return value;
	}

	int minQuantized = -1;
	for( int i = begin + 1; i < end - remain_count + 2; ++i )
	{
		int quantized = quantize( begin, i, 1 ) + quantize( i, end, remain_count - 1 );
		
		if( minQuantized < 0 || minQuantized > quantized )
			minQuantized = quantized;
	}

	if( minQuantized < 0 )
		minQuantized = 0;

	value = minQuantized;
	checked = 1;
	return value;
}

int sectionQuantize( int begin, int end )
{	
	int sub_sum = begin == 0 ? sum[end-1] : sum[end-1] - sum[begin-1];
	int sub_square_sum = begin == 0 ? square_sum[end-1] : square_sum[end-1] - square_sum[begin-1];
	
	int m = static_cast<int>( std::floor( static_cast<double>(sub_sum) / (end-begin) + 0.5 ) );

	return sub_square_sum - 2 * m * sub_sum + m * m * ( end - begin );
}

