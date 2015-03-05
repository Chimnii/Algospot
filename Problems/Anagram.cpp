#include <stdio.h>
#include <string.h>
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

int main( int argc, char** argv )
{
	int numTestCase;
	my::cin >> numTestCase;

	char original[101], password[101];
	while( numTestCase-- )
	{
		int length_original, length_password;
		my::cin >> original >> password;
		length_original = strlen(original);
		length_password = strlen(password);

		if( length_original != length_password || strcmp(original, password) != 0 )
		{
			std::sort( original, original + length_original );
			std::sort( password, password + length_password );
			if( strcmp( original, password ) == 0 )
			{
				printf("Yes\n");
			}
			else
			{
				printf("No.\n");
			}
		}
		else
		{
			printf("No.\n");
		}
	}

	return 0;
}