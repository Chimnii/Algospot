#include <stdio.h>
#include <string.h>
#include <queue>

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


char record[8][8][8][8][8][8][8][8];

struct state
{
	char count;
	char seq[8] = {0,};
	state()
	{
		count = 0;
	}
	state(const state& other)
	{
		count = other.count;
		memcpy(seq, other.seq, sizeof(seq));
	}
	state& operator=(const state& other)
	{
		count = other.count;
		memcpy(seq, other.seq, sizeof(seq));
	}

	char& get()
	{
		return record[seq[0]][seq[1]][seq[2]][seq[3]][seq[4]][seq[5]][seq[6]][seq[7]];
	}

	void reverse( int begin, int range )
	{
		int left = begin, right = begin+range-1;
		while( left < right )
		{
			char temp = seq[left];
			seq[left] = seq[right];
			seq[right] = temp;

			++left;
			--right;
		}
	}
};

void fill( char n, std::queue<state>& queue )
{
	while(queue.size() > 0)
	{
		state& curr = queue.front();

		char& rec = curr.get();

		if( rec == -1 || rec >= curr.count )
		{
			rec = curr.count;

			for( int range = 2; range <= n; ++range )
			{
				for( int i = 0; i <= n-range; ++i )
				{
					state rev(curr);
					++rev.count;
					rev.reverse(i, range);

					char& revrec = rev.get();
					if( revrec == -1 || rev.count < revrec )
					{
						revrec = rev.count;
						queue.push(rev);
					}
				}
			}
		}

		queue.pop();
	}
}

int main( int argc, char** argv )
{
	memset(record, -1, sizeof(record));
	for( int i = 1; i <= 8; ++i )
	{
		state base;
		for( int j = 0; j < i; ++j )
		{
			base.seq[j] = j;
		}

		std::queue<state> queue;
		queue.push(base);
		fill( i, queue );
	}

	int num_testcase;
	my::cin >> num_testcase;

	while( num_testcase-- )
	{
		int length;
		my::cin >> length;

		int seq[8];
		for( int i = 0; i < length; ++i )
		{
			my::cin >> seq[i];
		}

		// to 0~7
		state in;
		for( char nth = 0; nth < length; ++nth )
		{
			int min = 1000001, min_index = -1;
			for( char index = 0; index < length; ++index )
			{
				if( seq[index] < nth )
					continue;
				if( seq[index] < min )
				{
					min = seq[index];
					min_index = index;
				}
			}
			seq[min_index] = nth;
			in.seq[min_index] = nth;
		}

		char& out = in.get();
		printf("%d\n", out);
	}

	return 0;
}
