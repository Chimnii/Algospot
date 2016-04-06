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

namespace mod
{
	int sum( int a, int b, int mod )
	{
		return (a+b)%mod;
	}

	int sub( int a, int b, int mod )
	{
		return (a-b+mod)%mod;
	}

	int pow( int base, int exp, int mod )
	{
		long long pow_base = base;
		int accum = 1;
		while( exp != 0 )
		{
			pow_base %= mod;
			if( exp%2 != 0 )
				accum = (pow_base*accum)%mod;
			pow_base = pow_base*pow_base;
			exp /= 2;
		}
		return accum;
	}

	int div( int denom, int num, int mod )
	{
		int rev = pow( denom, mod-2, mod );
		int div = ((long long)num*rev)%mod;
		return div;
	}
}



int main( int argc, char** argv )
{
	int num_testcase;
	my::cin >> num_testcase;

	const int MOD = 1000000007;
	while( num_testcase-- )
	{
		int min_digit, max_digit, num_kind;
		my::cin >> min_digit >> max_digit >> num_kind;

		int comb;
		if( num_kind == 1 )
		{
			comb = ((long long)(max_digit - min_digit + 1)) % MOD;
		}
		else
		{
			comb = mod::div( num_kind-1, mod::sub( mod::pow( num_kind, max_digit+1, MOD ), mod::pow( num_kind, min_digit, MOD ), MOD ), MOD );
		}
		printf("%d\n", comb);
	}

	return 0;
}
