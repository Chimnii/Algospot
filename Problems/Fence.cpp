#include <stdio.h>
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

struct Rect
{
	int index, height;
	Rect() : index(0), height(0) {}
	Rect( int i, int h ) : index(i), height(h) {}
};

int lastIndex, maxRect;
Rect rects[200000];

void calcMaxRect( int index, int height );
inline void calcMax( int& max, int value ){ if( max < value ) max = value; }
inline void calcMin( int& min, int value ){ if( min > value ) min = value; }

int main( int argc, char** argv )
{
	int numTestCase;
	my::cin >> numTestCase;

	while( numTestCase-- )
	{
		int numFence;
		my::cin >> numFence;

		lastIndex = -1;
		maxRect = 0;
		for( int i = 0; i < numFence; ++i )
		{
			int height;
			my::cin >> height;
			calcMaxRect( i, height );
		}

		for( int i = 0; i < lastIndex + 1; ++i )
		{
			calcMax( maxRect, rects[i].height * ( numFence - rects[i].index ) );
		}

		printf("%d\n", maxRect );
	}

	return 0;
}

void calcMaxRect( int index, int height )
{
	int minIndex = index;
	while( lastIndex >= 0 && rects[lastIndex].height > height )
	{
		calcMax( maxRect, rects[lastIndex].height * ( index - rects[lastIndex].index ) );
		calcMin( minIndex, rects[lastIndex].index );
		--lastIndex;
	}

	++lastIndex;
	rects[lastIndex].index = minIndex;
	rects[lastIndex].height = height;
}