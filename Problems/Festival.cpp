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


int main( int argc, char** argv )
{
	int numTestCase;
	my::cin >> numTestCase;

	int numCost, numTeam;
	int costs[1000];
	while( numTestCase-- )
	{
		my::cin >> numCost >> numTeam;
		for( int i = 0; i < numCost; ++i )
		{
			my::cin >> costs[i];
		}

		int minimumSum = 1000000, minimumSumCount = 1000;
		for( int i = 0; i < numCost - numTeam + 1; ++i )
		{
			int sum = 0, count;
			for( int j = i; j < numCost && j < i + numTeam * 2 - 1; ++j )
			{
				sum += costs[j];
				count = (j - i + 1);
				if( count >= numTeam )
				{
					if( minimumSum * count > sum * minimumSumCount )
					{
						minimumSum = sum;
						minimumSumCount = count;
					}
				}
			}
		}

		printf("%.10f\n", static_cast<double>(minimumSum) / minimumSumCount);
	}
}