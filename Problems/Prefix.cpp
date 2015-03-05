#include <stdio.h>
#include <string>

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


int numWord, numPrefix;
int prevCount[201], maxCount[201];
std::string prevPrefix[201], maxPrefix[201];
std::string dictionary[3000];

void search();
int main( int argc, char** argv )
{
	int numTestCase;
	my::cin >> numTestCase;

	while( numTestCase-- )
	{
		my::cin >> numWord >> numPrefix;
		for( int i = 0; i < numWord; ++i )
		{
			char str[201];
			my::cin >> str;
			dictionary[i] = str;
		}

		search();

		for( int i = 1; i <= numPrefix; ++i )
		{
			printf( "%s\n", maxPrefix[i].c_str() );
		}
	}

	return 0;
}

void search()
{
	for( int i = 1; i <= numPrefix; ++i )
	{
		prevCount[i] = 0;
		maxCount[i] = 0;
		prevPrefix[i] = "";
		maxPrefix[i] = "";
	}

	std::string prefix;
	prefix.reserve(201);
	for( int w_i = 0; w_i < numWord; ++w_i )
	{
		prefix = "";
		int length = dictionary[w_i].length();
		for( int p_i = 1; p_i <= length; ++p_i )
		{
			prefix += dictionary[w_i][p_i-1];
			if( prefix == prevPrefix[p_i] )
			{
				++prevCount[p_i];
			}
			else
			{
				prevPrefix[p_i] = prefix;
				prevCount[p_i] = 1;
			}

			if( maxCount[p_i] < prevCount[p_i] )
			{
				maxCount[p_i] = prevCount[p_i];
				maxPrefix[p_i] = prevPrefix[p_i];
			}
		}
	}
}