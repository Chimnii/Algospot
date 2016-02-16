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

int num_stone;
int torches[200000];
int checked[200000];

void calc_checked();
int calc_minimum();
int main( int argc, char** argv )
{
	int num_testcase;
	my::cin >> num_testcase;

	while( num_testcase-- )
	{
		my::cin >> num_stone;

		for( int i = 0; i < num_stone; ++i )
		{
			my::cin >> torches[i];
			checked[i] = 0;
		}

		calc_checked();
		int min = calc_minimum();
		printf("%d\n", min);
	}

	return 0;
}

void calc_checked()
{
	for( int i = 0; i < num_stone; ++i )
	{
		++checked[ std::max( 0, i - torches[i] + 1 ) ];
	}

	int check = 1;
	for( int i = 0; i < num_stone; ++i )
	{
		check += checked[i] - 1;
		checked[i] = check;
	}
}

int calc_minimum()
{
	int torch_count = 0;

	int max_torch_range = -1, target_max_torch_range = -1;
	int target = 0;
	while( target < num_stone )
	{
		int check = checked[target];
		int index = target;
		while( check > 0 && index < num_stone )
		{
			int torch_l_range = index - torches[index] + 1;
			int torch_r_range = index + torches[index] - 1;

			if( torch_l_range <= target )
			{
				--check;
				my::calc_max( target_max_torch_range, torch_r_range );
			}
			my::calc_max( max_torch_range, torch_r_range );
			++index;
		}
		while( index <= target_max_torch_range && index < num_stone )
		{
			int torch_r_range = index + torches[index] - 1;

			my::calc_max( max_torch_range, torch_r_range );
			++index;
		}

		++torch_count;
		target = target_max_torch_range + 1;
		target_max_torch_range = max_torch_range;
	}


	return torch_count;
}

/*
100
9
1 2 2 1 3 1 1 2 4

*/
