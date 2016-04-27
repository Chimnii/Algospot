#include <stdio.h>
#include <string>

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

const int SIZE = 201;
const int MAX_NUMBER = 100000000;
int ncr[SIZE][SIZE];

void set_ncr();
int get_wordcount( int num_a, int num_b );
void get_word( std::string& word, int num_a, int num_b, int word_index );
int main( int argc, char** argv )
{
	set_ncr();
	int num_testcase;
	my::cin >> num_testcase;

	while( num_testcase-- )
	{
		int num_a, num_b, word_index;
		my::cin >> num_a >> num_b >> word_index;

		int wordcount = get_wordcount( num_a, num_b );
		if( wordcount == -1 || wordcount >= word_index )
		{
			std::string word = "";
			get_word( word, num_a, num_b, word_index );
			printf("%s\n", word.c_str());
		}
		else
			printf("NONE\n");
	}

	return 0;
}

void set_ncr()
{
	ncr[0][0] = 0;

	for( int n = 1; n < SIZE; ++n )
	{
		ncr[n][0] = 1;
		ncr[n][n] = 1;
	}

	for( int n = 2; n < SIZE; ++n )
	{
		for( int r = 1; r < n; ++r )
		{
			ncr[n][r] = ncr[n-1][r-1] + ncr[n-1][r];
			if( ncr[n-1][r-1] == -1 || ncr[n-1][r] == -1 || ncr[n][r] > MAX_NUMBER )
				ncr[n][r] = -1;
		}
	}
}

int get_wordcount( int num_a, int num_b )
{
	if( num_a < 0 || num_b < 0 )
		return 0;

	return ncr[num_a+num_b][num_a];
}

void get_word( std::string& word, int num_a, int num_b, int word_index )
{
	if( num_a == 0 && num_b == 0 )
		return;

	int wordcount = get_wordcount( num_a-1, num_b );
	if( wordcount == -1 || num_b == 0 || word_index <= wordcount )
	{
		word += 'a';
		return get_word( word, num_a-1, num_b, word_index );
	}
	else
	{
		word += 'b';
		return get_word( word, num_a, num_b-1, word_index - wordcount );
	}
}
