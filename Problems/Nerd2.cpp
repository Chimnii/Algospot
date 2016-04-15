#include <stdio.h>
#include <map>
#include <functional>

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

std::map<int, int> nerds;
int main( int argc, char** argv )
{
	int num_testcase;
	my::cin >> num_testcase;

	while( num_testcase-- )
	{
		long long sum = 0;
		nerds.clear();

		int num_person;
		my::cin >> num_person;
		for( int i = 0; i < num_person; ++i )
		{
			int prob, noodle;
			my::cin >> prob >> noodle;
			
			auto it = nerds.lower_bound(prob);
			if( it != nerds.end() && it->second > noodle )
			{
				sum += nerds.size();
				continue;
			}

			while( it != nerds.begin() && --it != nerds.end() && it->first < prob && it->second < noodle )
				it = nerds.erase(it);

			nerds.insert(it, std::make_pair(prob,noodle));
			sum += nerds.size();

			//for each (auto it in nerds) printf("%d %d\n", it.first, it.second);
		}
		printf("%lld\n", sum);
	}

	return 0;
}
