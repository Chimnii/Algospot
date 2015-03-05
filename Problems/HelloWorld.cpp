#include <stdio.h>

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
	
	char str[51];
	while( numTestCase-- )
	{
		my::cin >> str;
		printf("Hello, %s!\n", str);
	}
}

/*
#include <iostream>
#include <string>

int main( int argc, char** argv )
{
	int numTestCase;
	std::cin >> numTestCase;

	while( numTestCase-- )
	{
		std::string str;
		std::cin >> str;
		std::cout << "Hello, " << str << "!" << std::endl;
	}

	return 0;
}
*/