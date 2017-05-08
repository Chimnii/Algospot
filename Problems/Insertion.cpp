#include <cstdio>
#include <vector>
#include <set>

namespace my
{
#ifdef __GNUC__
#define getchar getchar_unlocked
#endif

	struct istream{};
	istream cin;

	inline bool is_num( char c ){ return ( c >= '0' && c <= '9' ); }
	inline istream& operator>>( istream& in, int& out )
	{
		char c; out = 0;
		while( c = getchar() ){ if( is_num(c) ){ out += (c-'0'); break; } }
		while( c = getchar() ){ if( !is_num(c) ) break; out *= 10; out += (c-'0'); }
		return in;
	}
}

int main( int argc, char** argv )
{
	int num_testcase;
	my::cin >> num_testcase;

	while( num_testcase-- )
	{
		int seq_length;
		my::cin >> seq_length;

		std::vector<int> moves, answers;
		std::set<int> naturals;

		for( int i = 1; i <= seq_length; ++i )
		{
			int move;
			my::cin >> move;
			moves.emplace_back(move);

			naturals.emplace_hint(naturals.end(), i);
		}

		while( moves.size() > 0 )
		{
			int move = moves.back();
			
			auto it = naturals.begin();
			std::advance(it, moves.size() - move - 1);

			answers.emplace_back(*it);
			naturals.erase(it);

			moves.pop_back();
		}

		for( auto it = answers.rbegin(); it != answers.rend(); ++it )
		{
			printf("%d ", *it);
		}
		printf("\n");
	}

	return 0;
}
