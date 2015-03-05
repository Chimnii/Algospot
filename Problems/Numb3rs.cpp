#include <stdio.h>
#include <string.h>
#include <vector>

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

int numTown, days, prison;
std::vector<int> roads[50];
double cached[101][51];

double getProb( int day, int town );
int main( int argc, char** argv )
{
	int numTestCase;
	my::cin >> numTestCase;

	while( numTestCase-- )
	{
		my::cin >> numTown >> days >> prison;

		int n;
		for( int i = 0; i < numTown; ++i )
		{
			roads[i].clear();
			roads[i].reserve(50);
			for( int j = 0; j < numTown; ++j )
			{
				my::cin >> n;
				if( n == 1 )
				{
					roads[i].push_back(j);
				}
			}
		}

		memset( cached, 0, sizeof(cached) );

		double firstProb = 1.0f / roads[prison].size();
		for( auto it = roads[prison].begin(); it != roads[prison].end(); ++it )
		{
			cached[1][*it] = firstProb;
		}

		int numProb, town;
		my::cin >> numProb;
		for( int i = 1; i <= numProb; ++i )
		{
			my::cin >> town;
			printf( "%.10f", getProb( days, town ) );
			printf( i != numProb ? " " : "\n" );
		}
	}

	return 0;
}

double getProb( int day, int town )
{
	if( cached[day][town] > 0 || day == 1 )
	{
		return cached[day][town];
	}

	double prob = 0;
	for( auto prev = roads[town].begin(); prev != roads[town].end(); ++prev )
	{
		prob += getProb( day-1, *prev ) / roads[*prev].size();
	}

	cached[day][town] = prob;
	return cached[day][town];
}
