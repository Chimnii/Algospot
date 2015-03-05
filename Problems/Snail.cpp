#include <stdio.h>
#include <iostream>
#include <cmath>

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
}

double calcProb( int, int );
int main( int argc, char** argv )
{
	int numTestCase;
	my::cin >> numTestCase;

	while( numTestCase-- )
	{
		int height, days;
		my::cin >> height >> days;

		double prob = 0;
		for( int r = days; r + days >= height && r >= 0; --r )
		{
			prob += calcProb( r, days-r );
		}

		printf( "%.10f\n", prob );
	}

	return 0;
}

double calcProb( int rainy, int sunny )
{
	double prob = 1;

	int min = std::min( rainy, sunny );
	for( int i = 1; i <= min; ++i )
	{
		prob *= 0.75 * 0.25 * ( rainy + sunny + 1 - i ) / i;
	}

	prob *= std::pow( rainy > sunny ? 0.75 : 0.25, std::abs( rainy - sunny ) );

	return prob;
}