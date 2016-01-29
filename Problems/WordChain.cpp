#include <stdio.h>
#include <string>
#include <vector>

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

	inline bool is_char( char c ){ return ( c > ' '  ); }
	inline istream& operator>>( istream& in, char* out )
	{
		char c;
		while( c = getchar() ){ if( is_char(c) ){ *out = c; ++out; break; } }
		while( c = getchar() ){ if( !is_char(c) ) break; *out = c; ++out; }
		*out = 0;
		return in;
	}

	inline istream& operator>>( istream&in, std::string& out )
	{
		static char temp[32];
		operator>>( in, temp );
		out = temp;
		return in;
	}
}

int num_word;

struct node
{
	std::string word;
	std::vector<node*> prevs, nexts;
} nodes[100];

int main( int argc, char** argv )
{
	int num_testcase;
	my::cin >> num_testcase;

	while( num_testcase-- )
	{
		my::cin >> num_word;
		for( int i = 0; i < num_word; ++i )
		{
			my::cin >> nodes[i].word;
			nodes[i].prevs.clear();
			nodes[i].nexts.clear();
		}

		for( int i = 0; i < num_word; ++i )
		{
			for( int j = i+1; j < num_word; ++j )
			{
				if( i == j )
					continue;

				if( *nodes[i].word.rbegin() == *nodes[j].word.begin() )
				{
					nodes[i].nexts.push_back(&nodes[j]);
					nodes[j].prevs.push_back(&nodes[i]);
				}
				if( *nodes[i].word.begin() == *nodes[j].word.rbegin() )
				{
					nodes[i].prevs.push_back(&nodes[j]);
					nodes[j].nexts.push_back(&nodes[i]);
				}
			}
		}

		printf("IMPOSSIBLE\n");
	}

	return 0;
}

/*
100
4
dog
god
dragon
need
3
aa
ab
bb
2
ab
cd
*/