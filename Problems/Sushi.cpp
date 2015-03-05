#include <stdio.h>

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
}

int num_sushi, budget;
int costs[20], prefs[20];

int calc_max_pref();
int main( int argc, char** argv )
{
	int num_testcase;
	my::cin >> num_testcase;

	while( num_testcase-- )
	{
		my::cin >> num_sushi >> budget;
		budget /= 100;

		for( int i = 0; i < num_sushi; ++i )
		{
			int cost, pref;
			my::cin >> cost >> pref;
			costs[i] = cost / 100;
			prefs[i] = pref;
		}

		int result = calc_max_pref();
		printf( "%d\n", result );
	}

	return 0;
}

const int MAX_INDEX = 200;
int calc_max_pref()
{
	int max_pref = 0;
	int sushis[MAX_INDEX] = {0,};

	for( int cost = 0; cost <= budget; ++cost )
	{
		int pref = sushis[cost%MAX_INDEX];

		if( cost != 0 && pref == 0 )
			continue;

		for( int i = 0; i < num_sushi; ++i )
		{
			int next_cost = cost + costs[i];
			int next_pref = pref + prefs[i];

			if( next_cost <= budget )
			{
				my::calc_max( sushis[next_cost%MAX_INDEX], next_pref );
				my::calc_max( max_pref, next_pref );
			}
		}
	}

	return max_pref;
}