#include <stdio.h>
#include <algorithm>

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


int numDollKind, numDominated;
int orderedDolls[100000];
int sortedDolls[100000];

void calc();
int main( int argc, char** argv )
{
	int numTestCase;
	my::cin >> numTestCase;

	while( numTestCase-- )
	{
		my::cin >> numDollKind >> numDominated;
		
		for( int i = 0; i < numDollKind; ++i )
		{
			my::cin >> orderedDolls[i];
			sortedDolls[i] = orderedDolls[i];
		}
		std::sort( sortedDolls, sortedDolls+numDollKind );

		calc();
	}

	return 0;
}

void calc()
{
	int cycle = 0;
	int totalDolls = 0;
	int sumMinDolls = 0;
	int remainDolls = 0;
	while(true)
	{
		if( totalDolls + ( sortedDolls[cycle] - sumMinDolls ) * ( numDollKind - cycle ) >= numDominated )
		{
			remainDolls = numDominated - totalDolls;
			break;
		}

		totalDolls += ( sortedDolls[cycle] - sumMinDolls ) * ( numDollKind - cycle );
		sumMinDolls += ( sortedDolls[cycle] - sumMinDolls );
		cycle += 1;
	}

	int remainKind = numDollKind - cycle;
	for( int i = 0; i < numDollKind; ++i )
	{
		if( i != 0 ) printf(" ");
		if( orderedDolls[i] > sumMinDolls && remainDolls > 0 )
		{
			int n = remainDolls / remainKind;
			if( remainDolls - n * remainKind > 0 ) ++n;
			printf( "%d", sumMinDolls + n );
			remainDolls -= n;
			remainKind -= 1;
		}
		else if( orderedDolls[i] >= sumMinDolls )
		{
			printf( "%d", sumMinDolls );
		}
		else
		{
			printf( "%d", orderedDolls[i] );
		}
	}
	printf("\n");
}

