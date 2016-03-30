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
	inline void calc_max( int& max, int value ){ if( max < value ) max = value; }
	inline void calc_min( int& min, int value ){ if( min > value ) min = value; }
}

int boards[100000];
int max_heights[16][32768];
int min_heights[16][32768];

std::pair<int,int> calc_minmax( int lboard, int rboard, int lindex, int rindex, int height, int index )
{
	if( lboard > rboard )
		return std::make_pair(99999,-1);
	if( lboard == rboard )
		return std::make_pair(boards[lboard], boards[lboard]);
	if( lboard+1 == rboard )
		return std::make_pair( std::min(boards[lboard], boards[rboard]), std::max(boards[lboard], boards[rboard]) );
	if( lboard == lindex && rboard == rindex )
		return std::make_pair( min_heights[height][index], max_heights[height][index] );

	int mindex = (lindex+rindex)/2;
	auto left = calc_minmax( lboard, std::min(rboard,mindex), lindex, mindex, height+1, index*2 );
	auto right = calc_minmax( std::max(lboard,mindex+1), rboard, mindex+1, rindex, height+1, index*2+1 );
	return std::make_pair( std::min(left.first, right.first), std::max(left.second, right.second) );
}

std::pair<int,int> fill( int lindex, int rindex, int height, int index )
{
	if( lindex > rindex )
		return std::make_pair(99999,-1);
	if( lindex == rindex )
		return std::make_pair(boards[lindex], boards[lindex]);
	if( lindex+1 == rindex )
		return ( boards[lindex] < boards[rindex] ? std::make_pair(boards[lindex], boards[rindex]) : std::make_pair(boards[rindex], boards[lindex]) );

	int mindex = (lindex+rindex)/2;
	auto left = fill( lindex, mindex, height+1, index*2 );
	auto right = fill( mindex+1, rindex, height+1, index*2+1 );

	max_heights[height][index] = std::max(left.second, right.second);
	min_heights[height][index] = std::min(left.first, right.first);
	return std::make_pair( min_heights[height][index], max_heights[height][index] );
}

int main( int argc, char** argv )
{
	int num_testcase;
	my::cin >> num_testcase;

	while( num_testcase-- )
	{
		int num_board, num_road;
		my::cin >> num_board >> num_road;

		for( int i = 0; i < num_board; ++i )
		{
			my::cin >> boards[i];
		}
		fill( 0, num_board-1, 0, 0 );

		int start, finish;
		for( int i = 0; i < num_road; ++i )
		{
			my::cin >> start >> finish;

			auto minmax = calc_minmax( start, finish, 0, num_board-1, 0, 0 );
			printf("%d\n", minmax.second - minmax.first);
		}
	}

	return 0;
}
