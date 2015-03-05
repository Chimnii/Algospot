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
}

int cached[101][101] = {0,};

int getMonoPoly( int rects, int first );
int main( int argc, char** argv )
{
	int numTestCase;
	my::cin >> numTestCase;

	cached[1][1] = 1;

	int numRect;
	while( numTestCase-- )
	{
		my::cin >> numRect;

		int polys = 0;
		for( int i = 1; i <= numRect; ++i )
		{
			polys += getMonoPoly( numRect, i );
			while( polys > 10000000 )
				polys -= 10000000;
		}
		printf( "%d\n", polys );
	}

	return 0;
}

int getMonoPoly( int rects, int first )
{
	if( rects == first )
	{
		return 1;
	}
	if( cached[rects][first] > 0 )
	{
		return cached[rects][first];
	}

	int polys = 0;
	for( int i = 1; i <= rects-first; ++i )
	{
		polys += ( first + i - 1 ) * getMonoPoly( rects-first, i );
		while( polys > 10000000 )
			polys -= 10000000;
	}
	
	cached[rects][first] = polys;

	return cached[rects][first];
}