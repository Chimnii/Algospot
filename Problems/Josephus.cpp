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

int N, K;
int man[1001];

void kill( int& begin, int& end, int& index );
void next( const int begin, const int end, int& index );
int main( int argc, char** argv )
{
	int num_testcase;
	my::cin >> num_testcase;

	while( num_testcase-- )
	{
		my::cin >> N >> K;
		for( int i = 1; i <= N; ++i )
		{
			man[i] = i;
		}

		int begin = 1, end = N+1, index = 1;
		while( end - begin > 2 )
		{
			kill( begin, end, index );
			next( begin, end, index );
		}
		
		if( man[begin] < man[end-1] ) printf( "%d %d\n", man[begin], man[end-1] );
		else printf( "%d %d\n", man[end-1], man[begin] );
	}

	return 0;
}

void kill( int& begin, int& end, int& index )
{
	if( index < ( begin + end ) /2 )
	{
		for( int i = index; i > begin; --i )
		{
			man[i] = man[i-1];
		}
		begin += 1;
	}
	else
	{
		for( int i = index; i < end-1; ++i )
		{
			man[i] = man[i+1];
		}
		end -= 1;
		index -= 1;
	}
}

void next( const int begin, const int end, int& index )
{
	int remain = end-begin;

	if( K > remain ) index += (K-1)%remain + 1;
	else index += K;

	if( index > end - 1 )
	{
		index -= remain;
	}
}