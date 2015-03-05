#include <stdio.h>
#include <string.h>
#include <cmath>

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

	inline istream& operator>>( istream& in, char& out )
	{
		char c;
		while( c = getchar() ){ if( IsChar(c) ){ out = c; break; } }
		return in;
	}
}

int main( int argc, char** argv )
{
	int numTestCase;
	my::cin >> numTestCase;

	double log26 = std::log((double)26);
	double log10 = std::log((double)10);

	char password[1001], selected[1001];
	while( numTestCase-- )
	{
		int numPassword;
		my::cin >> numPassword;

		double maxStrength = 0;
		while( numPassword-- )
		{
			int index = 0, alphabet = 0, numeric = 0;

			char c;
			my::cin >> c;
			while( my::IsChar(c) )
			{
				password[index++] = c;
				if( c >= 'a' && c <= 'z' ) ++alphabet;
				else ++numeric;
				c = getchar();
			}
			password[index] = 0;

			double strength = log26 * alphabet + log10 * numeric;
			if( strength > maxStrength )
			{
				maxStrength = strength;
				strcpy( selected, password );
			}
			else if( strength == maxStrength )
			{
				if( strcmp( password, selected ) < 0 )
					strcpy( selected, password );
			}
		}

		printf( "%s\n", selected );
	}

	return 0;
}
