#include <stdio.h>
#include <algorithm>

namespace my
{
	struct istream{};
	istream cin;

	inline bool is_num( char c ){ return ( c >= '0' && c <= '9' ); }
	inline bool is_negative( char c ){ return c == '-'; }
	inline istream& operator>>( istream& in, int& out )
	{
		char c; out = 0; bool neg = false;
		while( c = getchar() ){ if( is_negative(c) ){ neg = true; break; } if( is_num(c) ){ out += (c-'0'); break; } }
		while( c = getchar() ){ if( !is_num(c) ) break; out *= 10; out += (c-'0'); }
		if( neg ) out *= -1;
		return in;
	}
	inline istream& operator>>( istream& in, double& out )
	{
		char c; double under = 1.0; out = 0;
		while( c = getchar() ){ if( is_num(c) ){ out += (c-'0'); break; } }
		while( c = getchar() ){ if( !is_num(c) ) break; out *= 10; out += (c-'0'); }
		if( c == '.' ){ while( c = getchar() ){ if( !is_num(c) ) break; under *= 0.1; out += (c-'0')*under; } }
		return in;
	}
}

int num_camera, num_location;
double locations[200];
const double max = 241.0;

double calc_max_dist();
int main( int argc, char** argv )
{
	int num_testcase;
	my::cin >> num_testcase;

	while( num_testcase-- )
	{
		my::cin >> num_camera >> num_location;
		for( int i = 0; i < num_location; ++i )
		{
			my::cin >> locations[i];
		}

		printf("%.2f\n", calc_max_dist());
	}

	return 0;
}

double calc( int last, int remain, double dist )
{
	if( remain == 1 )
		return std::min( dist, locations[num_location-1] - locations[last] );
	if( remain > num_location - last )
		return 0;

	double max_dist = 0;
	for( int i = last+1; i < num_location; ++i )
	{
		double new_dist = std::min( dist, std::min( locations[i] - locations[last], (locations[num_location-1] - locations[i]) / (remain-1) ) );
		max_dist = std::max( max_dist, calc( i, remain-1, new_dist ) );
		if( locations[i] - locations[last] >= dist )
			break;
	}

	return max_dist;
}

double calc_max_dist()
{
	double dist = (locations[num_location-1] - locations[0]) / (num_camera-1);
	return calc( 0, num_camera-1, dist );
}