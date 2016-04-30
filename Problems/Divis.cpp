#include <stdio.h>
#include <string.h>

namespace my
{
#ifdef __GNUC__
#define getchar getchar_unlocked
#endif

	struct istream{};
	istream cin;

	inline bool is_char( char c ){ return ( c > ' '  ); }
	inline istream& operator>>( istream& in, char* out )
	{
		char c;
		while( c = getchar() ){ if( is_char(c) ){ *out = c; ++out; break; } }
		while( c = getchar() ){ if( !is_char(c) ) break; *out = c; ++out; }
		*out = 0;
		return in;
	}
}

const int denom = 61;
int digits[128];

void set_digits();
int main( int argc, char** argv )
{
	set_digits();

	char word[10000];
	while( my::cin >> word, strcmp(word, "end") )
	{
		int index = 0, mod = 0;
		while( word[index] )
		{
			mod += digits[word[index]];
			++index;
		}
		printf(mod % denom ? "no\n" : "yes\n");
	}

	return 0;
}

void set_digits()
{
	for( int i = 0 ; i < 10; ++i )
		digits['0'+i] = i;
	for( int i = 0; i < 26; ++i )
	{
		digits['A'+i] = 10 + i;
		digits['a'+i] = 10 + 26 + i;
	}
}
