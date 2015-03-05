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

	inline bool is_char( char c ){ return ( c > ' '  ); }
	inline void getline( char* out )
	{
		char c;
		while( c = getchar() ){ if( !is_char(c) && c != ' ' ) break; *out = c; ++out; }
		*out = 0;
	}
}

std::string turn( std::string& tree, int begin, int end );
int main( int argc, char** argv )
{
	int num_testcase;
	my::cin >> num_testcase;

	char sz_tree[1001];
	std::string tree;
	while( num_testcase-- )
	{
		my::getline(sz_tree);
		tree = sz_tree;

		printf( "%s\n", turn( tree, 0, tree.length() ).c_str() );
	}

	return 0;
}

std::string turn( std::string& tree, int begin, int end )
{
	int index = begin;
	if( tree[index++] != 'x' )
	{
		return tree.substr( begin, 1 );
	}

	int child_begin[4];

	int current_child = 0;
	int remain_index = 0;

	while( current_child < 4 )
	{
		if( remain_index == 0 )
		{
			child_begin[current_child++] = index;
			remain_index = 1;
			continue;
		}

		if( tree[index++] == 'x' )
		{
			remain_index += 4;
		}
		--remain_index;
	}


	return "x" + turn( tree, child_begin[2], child_begin[3] ) + turn( tree, child_begin[3], end ) + turn( tree, child_begin[0], child_begin[1] ) + turn( tree, child_begin[1], child_begin[2] );
}
