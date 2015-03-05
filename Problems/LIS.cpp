#include <stdio.h>
#include <limits>

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

	inline void calcMax( int& max, int value ){ if( max < value ) max = value; }
}

int search( int lis[501], int begin, int end, int target )
{
	int mid;
	while( begin < end )
	{
		mid = (begin+end) / 2;
		if( target > lis[mid] )
			begin = mid + 1;
		else
			end = mid;
	}

	return begin;
}

int main( int argc, char** argv )
{
	int numTestCase;
	my::cin >> numTestCase;

	int last_of_lis[501];
	while( numTestCase-- )
	{
		int length;
		my::cin >> length;

		int lis = 0;

		int n;
		for( int i = 1; i <= length; ++i )
		{
			my::cin >> n;
			last_of_lis[i] = std::numeric_limits<int>::max();

			int index = search( last_of_lis, 1, lis + 1, n );
			if( n < last_of_lis[index] )
			{
				last_of_lis[index] = n;
				my::calcMax( lis, index );
			}
		}

		printf( "%d\n", lis );
	}

	return 0;
}
