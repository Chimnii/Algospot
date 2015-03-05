#include <iostream>
#include <algorithm>
#include <stdio.h>

namespace my
{
	struct istream{};
	istream cin;

	inline bool IsMinus( char c ){ return ( c == '-' ); }
	inline bool IsNum( char c ){ return ( c >= '0' && c <= '9' ); }
	inline istream& operator>>( istream& in, int& out )
	{
		char c; out = 0; bool m = false;
		while( c = getchar() ){ if( IsMinus(c) ){ m = true; } else if( IsNum(c) ){ out += (c-'0'); break; } }
		while( c = getchar() ){ if( !IsNum(c) ) break; out *= 10; out += (c-'0'); }
		if( m ) out *= -1;
		return in;
	}
}

int main( int argc, char** argv )
{
	int numTestCase;
	my::cin >> numTestCase;

	while( numTestCase-- )
	{
		int numPoint;
		my::cin >> numPoint;

		std::pair<int, int> points[20000];
		for( int i = 0; i < numPoint; ++i )
		{
			my::cin >> points[i].first >> points[i].second;
		}
		std::sort( points, points+numPoint );

		
		int minLength = 200000000, maxLength = 0;

		int lb = 0, lt = 1;
		while( lb < numPoint && lt < numPoint )
		{
			if( points[lb].first == points[lt].first )
			{
				int r = lt + 1;
				bool findRB = false, findRT = false;
				while( r < numPoint )
				{
					if( points[r].first - points[lb].first == points[lt].second - points[lb].second )
					{	
						while( r < numPoint && points[r].first - points[lb].first == points[lt].second - points[lb].second )
						{
							if( points[r].second == points[lb].second )
								findRB = true;
							if( points[r].second == points[lt].second )
								findRT = true;
							++r;
						}

						break;
					}

					++r;
				}

				if( findRB && findRT )
				{
					int length = points[lt].second - points[lb].second;
					if( maxLength < length )
						maxLength = length;
					if( minLength > length )
						minLength = length;
				}

				++lt;
			}
			else
			{
				++lb;
				lt = lb+1;
			}
		}

		printf( "%d %d\n", minLength, maxLength );
	}

	return 0;
}