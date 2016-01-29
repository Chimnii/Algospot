#include <stdio.h>
#include <vector>
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
}

int main( int argc, char** argv )
{
	int num_testcase;
	my::cin >> num_testcase;

	while( num_testcase-- )
	{
		int num_student;
		my::cin >> num_student;

		int scores[40];
		for( int i = 0; i < num_student; ++i )
		{
			my::cin >> scores[i];
		}

		std::sort(&scores[0], &scores[num_student]);

		double max_score = 0;
		for( int i = 0; i <= (num_student-1)/2; ++i )
		{
			double score = 1.0 * (scores[i] + scores[num_student-i-1]) / 2;
			if( score > max_score )
				max_score = score;
		}

		printf("%.1f\n", max_score);
	}

	return 0;
}
