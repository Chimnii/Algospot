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
}

int pre[100], in[100], post[100];

void get_post( int pre_begin, int pre_end, int in_begin, int in_end, int post_begin, int post_end );
int main( int argc, char** argv )
{
	int num_testcase;
	my::cin >> num_testcase;

	while( num_testcase-- )
	{
		int num_node;
		my::cin >> num_node;

		for( int i = 0; i < num_node; ++i )
			my::cin >> pre[i];
		for( int i = 0; i < num_node; ++i )
			my::cin >> in[i];
		get_post( 0, num_node, 0, num_node, 0, num_node );
		for( int i = 0; i < num_node; ++i )
			printf("%d ", post[i]);
		printf("\n");
	}

	return 0;
}

void get_post( int pre_begin, int pre_end, int in_begin, int in_end, int post_begin, int post_end )
{
	if( pre_begin == pre_end )
		return;

	for( int i = 0; i < in_end-in_begin; ++i )
	{
		if( in[i+in_begin] == pre[pre_begin] )
		{
			get_post( pre_begin+1, pre_begin+1+i, in_begin, in_begin+i, post_begin, post_begin+i );
			get_post( pre_begin+1+i, pre_end, in_begin+i+1, in_end, post_begin+i, post_end-1 );
			post[post_end-1] = pre[pre_begin];
		}
	}
}
