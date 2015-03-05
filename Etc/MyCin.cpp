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

	inline istream& operator>>( istream& in, long long& out )
	{
		char c; out = 0;
		while( c = getchar() ){ if( is_num(c) ){ out += (c-'0'); break; } }
		while( c = getchar() ){ if( !is_num(c) ) break; out *= 10; out += (c-'0'); }
		return in;
	}

	inline istream& operator>>( istream& in, float& out )
	{
		char c; float under = 1.0f; out = 0;
		while( c = getchar() ){ if( is_num(c) ){ out += (c-'0'); break; } }
		while( c = getchar() ){ if( !is_num(c) ) break; out *= 10; out += (c-'0'); }
		if( c == '.' ){ while( c = getchar() ){ if( !is_num(c) ) break; under *= 0.1f; out += (c-'0')*under; } }
		return in;
	}

	inline istream& operator>>( istream& in, double& out )
	{
		char c; double under = 1.0; out = 0;
		while( c = getchar() ){ if( is_num(c) ){ out += (c-'0'); break; } }
		while( c = getchar() ){ if( !is_num(c) ) break; out *= 10; out += (c-'0'); }
		if( c == '.' ){ while( c = getchar() ){ if( !is_num(c) ) break; under *= 0.1; out += (c-'0')*under; } }
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

	inline istream& operator>>( istream& in, char& out )
	{
		char c;
		while( c = getchar() ){ if( is_char(c) ){ out = c; break; } }
		return in;
	}

	inline void getline( char* out )
	{
		char c;
		while( c = getchar() ){ if( !is_char(c) && c != ' ' ) break; *out = c; ++out; }
		*out = 0;
	}

	inline void calc_max( int& max, int value ){ if( max < value ) max = value; }
	inline void calc_min( int& min, int value ){ if( min > value ) min = value; }

	template<typename T, T X>
	struct default_type
	{
		T val;
		default_type() : val(X) {}
		default_type( T& other ) : val(other) {}
		operator T&(){ return val; }
	};
}

int main( int argc, char** argv )
{
	int num_testcase;
	my::cin >> num_testcase;

	while( num_testcase-- )
	{
	}

	return 0;
}
