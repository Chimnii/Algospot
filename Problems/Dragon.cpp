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


enum e_curve
{
	FX,
	YF
};

long long generation_letters[51];
long long generation_half_letters[51];
int curve_generation, curve_order, curve_length;

void print_curve_string( e_curve curve, int remain_gen, int order, int length );
int main( int argc, char** argv )
{
	generation_letters[0] = 2;
	generation_half_letters[0] = 1;
	for( int i = 1; i <= 50; ++ i ){ generation_letters[i] = generation_letters[i-1] * 2 + 1; generation_half_letters[i] = generation_letters[i] / 2; }

	int num_testcase;
	my::cin >> num_testcase;

	while( num_testcase-- )
	{
		my::cin >> curve_generation >> curve_order >> curve_length;
		print_curve_string( FX, curve_generation, curve_order, curve_length );
		printf("\n");
	}

	return 0;
}

void print_curve( e_curve curve, int order, int length )
{
	if( curve == FX )
	{
		if( length == 1 ) printf( order == 1 ? "F" : "X" );
		else printf("FX");
	}
	else
	{
		if( length == 1 ) printf( order == 1 ? "Y" : "F" );
		else printf("YF");
	}
}

void print_curve_string( e_curve curve, int remain_gen, int order, int length )
{
	if( remain_gen == 0 )
	{
		print_curve( curve, order, length );
		return;
	}

	long long half_letters = generation_half_letters[remain_gen];

	bool left_print = order <= half_letters;
	bool center_print = order <= half_letters+1 && order+length-1 >= half_letters+1;
	bool right_print = order+length-1 >= half_letters+2;

	if( left_print )
	{
		int next_length = center_print ? static_cast<int>(half_letters-order+1) : length;
		print_curve_string( FX, remain_gen-1, order, next_length );
	}

	if( center_print )
	{
		printf( curve == FX ? "+" : "-" );
	}

	if( right_print )
	{
		int next_order = center_print ? 1 : static_cast<int>(order-half_letters-1);
		int next_length = center_print ? static_cast<int>(order+length-half_letters-2) : length;
		print_curve_string( YF, remain_gen-1, next_order, next_length );
	}
}
