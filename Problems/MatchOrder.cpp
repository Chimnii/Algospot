#include <stdio.h>
#include <string>

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
}

int main( int argc, char** argv )
{
	int num_testcase;
	my::cin >> num_testcase;

	while( num_testcase-- )
	{
		int num_player;
		my::cin >> num_player;

		int their_rating[100], our_rating[100];
		for( int i = 0; i < num_player; ++i )
			my::cin >> their_rating[i];
		for( int i = 0; i < num_player; ++i )
			my::cin >> our_rating[i];

		int win_count = 0;
		bool check_player[100] = {0, };
		for( int ti = 0; ti < num_player; ++ti )
		{
			int min_win_rating = 4001, min_win_index;
			for( int oi = 0; oi < num_player; ++oi )
			{
				if( !check_player[oi] && our_rating[oi] >= their_rating[ti] && our_rating[oi] < min_win_rating )
				{
					min_win_rating = our_rating[oi];
					min_win_index = oi;
				}
			}

			if( min_win_rating < 4001 )
			{
				check_player[min_win_index] = true;
				++win_count;
				continue;
			}

			for( int oi = 0; oi < num_player; ++oi )
			{
				if( !check_player[oi] && our_rating[oi] < min_win_rating )
				{
					min_win_rating = our_rating[oi];
					min_win_index = oi;
				}
			}

			check_player[min_win_index] = true;
		}

		printf("%d\n", win_count);
	}

	return 0;
}
