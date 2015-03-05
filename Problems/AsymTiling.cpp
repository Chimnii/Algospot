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

int answers[101] = {0,0,0,2,2,6,8,18,26,50,76,136,212,364,576,966,1542,2550,4092,6710,10802,17622,28424,46224,74648,121160,195808,317434,513242,831430,1344672,2177322,3521994,5701290,9223284,14927768,24151052,39083988,63235040,102327390,165562430,267903350,433465780,701391022,134856795,836283239,971140034,807480580,778620607,586193916,364814516,951158482,315972991,267374252,583347243,851114331,434461567,286211513,720673080,7913044,728586124,738163248,466749365,207605144,674354509,886316271,560670773,454036193,14706959,480148926,494855885,993459741,488315619,511636057,999951676,559903360,559855029,197934720,757789749,82216434,840006183,126890920,966897103,424948298,391845394,352622277,744467671,964078815,708546479,75442739,783989218,129238276,913227494,715089548,628317035,285836680,914153715,815044277,729197985,101726241,830924226};
int main( int argc, char** argv )
{
	int numTestCase;
	my::cin >> numTestCase;

	int width;
	while( numTestCase-- )
	{
		my::cin >> width;
		printf( "%d\n", answers[width] );
	}

	return 0;
}

/*
int tiling[101] = {0,};
int symTiling[101] = {0,};

int getTiling( int n );
int getSymTiling( int n );
int main( int argc, char** argv )
{
	int numTestCase;
	my::cin >> numTestCase;

	tiling[0] = 0;
	tiling[1] = 1;
	tiling[2] = 2;
	symTiling[0] = 0;
	symTiling[1] = 1;
	symTiling[2] = 2;

	int width;
	while( numTestCase-- )
	{
		my::cin >> width;

		int result = getTiling(width) - getSymTiling(width);
		while( result < 0 )
			result += 1000000007;
		printf( "%d\n", result );
	}

	return 0;
}

int getTiling( int n )
{
	if( tiling[n] > 0 )
	{
		return tiling[n];
	}

	tiling[n] = getTiling(n-1) + getTiling(n-2);
	while( tiling[n] > 1000000007 )
		tiling[n] -= 1000000007;

	return tiling[n];
}

int getSymTiling( int n )
{
	if( symTiling[n] > 0 )
	{
		return symTiling[n];
	}

	if( n%2 == 1 )
	{
		symTiling[n] = getTiling( (n-1)/2 );
	}
	else
	{
		symTiling[n] = getTiling( n/2 ) + getTiling( (n-2)/2 );
	}

	while( symTiling[n] > 1000000007 )
		symTiling[n] -= 1000000007;

	return symTiling[n];
}
*/