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

	inline bool IsChar( char c ){ return ( c > ' '  ); }
	inline istream& operator>>( istream& in, char* out )
	{
		char c;
		while( c = getchar() ){ if( IsChar(c) ){ *out = c; ++out; break; } }
		while( c = getchar() ){ if( !IsChar(c) ) break; *out = c; ++out; }
		*out = 0;
		return in;
	}

	inline void calcMax( int& max, int value ){ if( max < value ) max = value; }
	inline void calcMin( int& min, int value ){ if( min > value ) min = value; }
}

char sequence[10001];
int calcMinimumDifficult();
int main( int argc, char** argv )
{
	int numTestCase;
	my::cin >> numTestCase;

	while( numTestCase-- )
	{
		my::cin >> sequence;
		printf( "%d\n", calcMinimumDifficult() );
	}

	return 0;
}

int calcDiff( int l, int len )
{
	char* s = sequence;
	if( len == 3 )
	{
		if( s[l] == s[l+1] && s[l+1] == s[l+2] ) return 1;
		if( s[l]+1 == s[l+1] && s[l+1]+1 == s[l+2] ) return 2;
		if( s[l]-1 == s[l+1] && s[l+1]-1 == s[l+2] ) return 2;
		if( s[l] == s[l+2] ) return 4;
		if( s[l]-s[l+1] == s[l+1]-s[l+2] ) return 5;
	}
	else if( len == 4 )
	{
		if( s[l] == s[l+1] && s[l+1] == s[l+2] && s[l+2] == s[l+3] ) return 1;
		if( s[l]+1 == s[l+1] && s[l+1]+1 == s[l+2] && s[l+2]+1 == s[l+3] ) return 2;
		if( s[l]-1 == s[l+1] && s[l+1]-1 == s[l+2] && s[l+2]-1 == s[l+3] ) return 2;
		if( s[l] == s[l+2] && s[l+1] == s[l+3] ) return 4;
		if( s[l]-s[l+1] == s[l+1]-s[l+2] && s[l+1]-s[l+2] == s[l+2]-s[l+3] ) return 5;
	}
	else if( len == 5 )
	{
		if( s[l] == s[l+1] && s[l+1] == s[l+2] && s[l+2] == s[l+3] && s[l+3] == s[l+4] ) return 1;
		if( s[l]+1 == s[l+1] && s[l+1]+1 == s[l+2] && s[l+2]+1 == s[l+3] && s[l+3]+1 == s[l+4] ) return 2;
		if( s[l]-1 == s[l+1] && s[l+1]-1 == s[l+2] && s[l+2]-1 == s[l+3] && s[l+3]-1 == s[l+4] ) return 2;
		if( s[l] == s[l+2] && s[l+1] == s[l+3] && s[l+2] == s[l+4] ) return 4;
		if( s[l]-s[l+1] == s[l+1]-s[l+2] && s[l+1]-s[l+2] == s[l+2]-s[l+3] && s[l+2]-s[l+3] == s[l+3]-s[l+4] ) return 5;
	}

	return 10;
}

int calcMinimumDifficult()
{
	int minDiff[10001] = {0,};

	minDiff[0] = 999;
	minDiff[1] = 999;
	minDiff[2] = calcDiff( 0, 3 );
	minDiff[3] = calcDiff( 0, 4 );
	minDiff[4] = calcDiff( 0, 5 );

	int i = 5;
	while( sequence[i] )
	{
		minDiff[i] = minDiff[i-3] + calcDiff( i-2, 3 );
		my::calcMin( minDiff[i], minDiff[i-4] + calcDiff( i-3, 4 ) );
		my::calcMin( minDiff[i], minDiff[i-5] + calcDiff( i-4, 5 ) );
		++i;
	}

	return minDiff[i-1];

	return 0;
}