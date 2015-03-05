#include <stdio.h>
#include <string.h>

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
	inline void calcMax( int& max, int value ){ if( max < value ) max = value; }
	inline void calcMin( int& min, int value ){ if( min > value ) min = value; }
}

int length_A, length_B;
int seq_A[101], seq_B[101];
int cachedJLIS[101][101];

int getJLIS( int index_A, int index_B );
int main( int argc, char** argv )
{
	int numTestCase;
	my::cin >> numTestCase;

	while( numTestCase-- )
	{
		my::cin >> length_A >> length_B;
		for( int a = 1; a <= length_A; ++a )
		{
			my::cin >> seq_A[a];
		}
		for( int b = 1; b <= length_B; ++b )
		{
			my::cin >> seq_B[b];
		}

		memset( cachedJLIS, 0, sizeof(cachedJLIS) );

		printf( "%d\n", getJLIS( 0, 0 ) - 2 );
	}

	return 0;
}


int getJLIS( int index_A, int index_B )
{
	if( cachedJLIS[index_A][index_B] != 0 )
	{
		return cachedJLIS[index_A][index_B];
	}

	int jlis = seq_A[index_A] == seq_B[index_B] ? 1 : 2;
	for( int next_A = index_A + 1; next_A <= length_A; ++next_A )
	{
		if( ( index_A == 0 || seq_A[index_A] < seq_A[next_A] ) && ( index_B == 0 || seq_B[index_B] < seq_A[next_A] ) )
		{
			my::calcMax( jlis, getJLIS( next_A, index_B ) + 1 );
		}
	}
	for( int next_B = index_B + 1; next_B <= length_B; ++next_B )
	{
		if( ( index_A == 0 || seq_A[index_A] < seq_B[next_B] ) && ( index_B == 0 || seq_B[index_B] < seq_B[next_B] ) )
		{
			my::calcMax( jlis, getJLIS( index_A, next_B ) + 1 );
		}
	}
	
	cachedJLIS[index_A][index_B] = jlis;
	return jlis;
}