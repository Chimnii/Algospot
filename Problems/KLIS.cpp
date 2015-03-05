#include <stdio.h>
#include <string.h>
#include <queue>
#include <limits>

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
	
	inline void calc_max( int& max, int value ){ if( max < value ) max = value; }
	inline void calc_min( int& min, int value ){ if( min > value ) min = value; }
}

int num_element, answer_order;
int max_lds;
int sequence[501];
int lds[501];
int lds_count[501];
const int MAX_COUNT = std::numeric_limits<int>::max();

void calc_lds();
void print_klis( int begin, int end, int lower, int remain_lds, int remain_order );
int main( int argc, char** argv )
{
	int num_testcase;
	my::cin >> num_testcase;

	while( num_testcase-- )
	{
		my::cin >> num_element >> answer_order;

		for( int i = 0; i < num_element; ++i )
		{
			my::cin >> sequence[i];
		}

		calc_lds();
		printf( "%d\n", max_lds );
		print_klis( 0, num_element, 0, max_lds, answer_order );
		printf("\n");
	}

	return 0;
}

void calc_lds()
{
	max_lds = 0;
	memset( lds, 0, sizeof(lds) );
	memset( lds_count, 0, sizeof(lds_count) );

	for( int ele_i = num_element-1; ele_i >= 0; --ele_i )
	{
		int curr_max_lds = 1;
		int curr_max_lds_count = 1;
		for( int lds_i = num_element-1; lds_i > ele_i; --lds_i )
		{
			if( sequence[ele_i] < sequence[lds_i] )
			{
				if( curr_max_lds < lds[lds_i] + 1 )
				{
					curr_max_lds = lds[lds_i] + 1;
					curr_max_lds_count = lds_count[lds_i];
				}
				else if( curr_max_lds == lds[lds_i] + 1 )
				{
					long long count_sum = (long long)curr_max_lds_count + lds_count[lds_i];
					curr_max_lds_count = count_sum > MAX_COUNT ? MAX_COUNT : (int)count_sum;
				}
			}
		}

		lds[ele_i] = curr_max_lds;
		lds_count[ele_i] = curr_max_lds_count;
		my::calc_max( max_lds, curr_max_lds );
	}
}

struct cached_data
{
	int index, element, count;
	cached_data() : index(0), element(0), count(0) {}
	cached_data( int i, int e, int c ) : index(i), element(e), count(c) {}
	bool operator< ( const cached_data& other ) const { return element < other.element; }
	bool operator> ( const cached_data& other ) const { return element > other.element; }
};

typedef std::priority_queue< cached_data, std::vector<cached_data>, std::greater<cached_data> > lds_queue;
void make_lds_queue( lds_queue& queue, int begin, int end, int lower, int remain_lds )
{
	for( int i = begin; i < end; ++i )
	{
		if( sequence[i] > lower && lds[i] == remain_lds )
		{
			queue.push( cached_data( i, sequence[i], lds_count[i] ) );
		}
	}
}

void print_klis( int begin, int end, int lower, int remain_lds, int remain_order )
{
	if( remain_lds <= 0 ) return;

	lds_queue queue;
	make_lds_queue( queue, begin,end, lower, remain_lds );

	while( queue.size() > 0 )
	{
		int index = queue.top().index;
		int element = queue.top().element;
		int count = queue.top().count;

		if( remain_order <= count )
		{
			printf( remain_lds > 1 ? "%d " : "%d", element );
			print_klis( index+1, end, element, remain_lds-1, remain_order );
			break;
		}
		else
		{
			remain_order -= count;
			queue.pop();
		}
	}
}