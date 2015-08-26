#include <stdio.h>
#include <vector>
#include <algorithm>

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

struct cbook
{
	int price, point, diff;
};
struct cstore
{
	std::vector<cbook> books;
};

cstore stores[101];

void sort_books( int index );
int calc_price( int index );

int main( int argc, char** argv )
{
	int num_testcase;
	my::cin >> num_testcase;

	while( num_testcase-- )
	{
		int num_book, num_store;
		my::cin >> num_book >> num_store;

		for( int st = 0; st < num_store; ++st )
		{
			stores[st].books.clear();
		}

		for( int b = 0; b < num_book; ++b )
		{
			for( int st = 0; st < num_store; ++st )
			{
				cbook book;
				my::cin >> book.price >> book. point;
				book.diff = book.point - book.price;

				stores[st].books.push_back(book);
			}
		}
		
		int min_total_price = 200*10000;
		for( int st = 0; st < num_store; ++st )
		{
			sort_books(st);
			int total_price = calc_price(st);
			if( total_price < min_total_price )
				min_total_price = total_price;
		}

		printf( "%d\n", min_total_price );
	}

	return 0;
}

bool compare_book( const cbook& b1, const cbook& b2 )
{
	if( b1.diff >= 0 && b2.diff >= 0 )
	{
		return b1.diff > b2.diff;
	}
	else if( b1.diff >= 0 )
	{
		return true;
	}
	else if( b2.diff >= 0 )
	{
		return false;
	}
	else
	{
		return b1.point > b2.point;
	}
}

void sort_books( int index )
{
	std::vector<cbook>& books = stores[index].books;
	
	std::sort( books.begin(), books.end(), compare_book );
}

int calc_price( int index )
{
	std::vector<cbook>& books = stores[index].books;

	int total_price = 0;
	int remain_point = 0;
	for( auto it = books.begin(); it != books.end(); ++it )
	{
		cbook book = *it;

		if( remain_point >= book.price )
		{
			remain_point -= book.price;
			remain_point += book.point;
		}
		else
		{
			total_price += book.price - remain_point;
			remain_point = book.point;
		}
	}

	return total_price;
}