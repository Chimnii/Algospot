#include <stdio.h>
#include <string.h>
#include <string>
#include <algorithm>

namespace my
{
	struct istream{};
	istream cin;

	inline bool IsNum( char c ){ return ( c >= '0' && c <= '9' ); }
	inline istream& operator>>( istream& in, int& out )
	{
		char c; out = 0;
		while( c = getchar() ){ if( IsNum(c) ){ out += (c-'0'); break; } }
		while( c = getchar() ){ if( !IsNum(c) ) break; out *= 10; out += (c-'0'); }
		return in;
	}

	inline bool IsChar( char c ){ return ( c > ' '  ); }
	inline istream& operator>>( istream& in, char* out )
	{
		char c;
		while( c = getchar() ){ if( IsChar(c) ){ *out = c; ++out; break; } }
		while( c = getchar() ){ if( !IsChar(c) ) break; *out = c; ++out; }
		*out = 0;
		return in;
	}
}

int numMatched;
int len_wildcard, len_filename;
char wildcard[101], filename[101];
std::string matched[50];

bool isMatched( int, int, int, int );
int main( int argc, char** argv )
{
	int numTestCase;
	my::cin >> numTestCase;
	
	while( numTestCase-- )
	{
		int numFile;
		my::cin >> wildcard >> numFile;

		numMatched = 0;
		while( numFile-- )
		{
			my::cin >> filename;

			len_wildcard = 0;
			int n = strlen(wildcard);
			for( int i = 0; i < n; ++i )
			{
				if( wildcard[i] != '*' )
					++len_wildcard;
			}
			len_filename = strlen(filename);

			if( isMatched( 0, len_wildcard, 0, len_filename ) )
			{
				matched[numMatched++] = filename;
			}
		}

		std::sort( matched, matched + numMatched );
		for( int i = 0; i < numMatched; ++i )
		{
			printf( "%s\n", matched[i].c_str() );
		}
	}

	return 0;
}

bool isMatched( int w_index, int w_remain, int f_index, int f_remain )
{
	if( w_remain == 0 && f_remain == 0 )
	{
		return true;
	}
	
	if( w_remain < 0 || f_remain < 0 )
	{
		return false;
	}

	if( w_remain > f_remain )
	{
		return false;
	}

	if( wildcard[w_index] == '?' || wildcard[w_index] == filename[f_index] )
	{
		return isMatched( w_index + 1, w_remain - 1, f_index + 1, f_remain - 1 );
	}
	else if( wildcard[w_index] == '*' )
	{
		return isMatched( w_index + 1, w_remain, f_index, f_remain ) || isMatched( w_index, w_remain, f_index + 1, f_remain - 1 );
	}

	return false;
}