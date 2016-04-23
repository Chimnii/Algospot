#include <stdio.h>
#include <queue>
#include <functional>

namespace my
{
#ifdef __GNUC__
#define getchar getchar_unlocked
#endif

	struct istream{};
	istream cin;

	inline bool is_num( char c ){ return ( c >= '0' && c <= '9' ); }
	inline istream& operator>>( istream& in, int& out )
	{
		char c; out = 0;
		while( c = getchar() ){ if( is_num(c) ){ out += (c-'0'); break; } }
		while( c = getchar() ){ if( !is_num(c) ) break; out *= 10; out += (c-'0'); }
		return in;
	}
}

const int seq_mod = 20090711;
int main( int argc, char** argv )
{
	int num_testcase;
	my::cin >> num_testcase;

	while( num_testcase-- )
	{
		int seq_length, seq_a, seq_b;
		my::cin >> seq_length >> seq_a >> seq_b;

		int seq = 1983;

		int mid = seq, sum = seq;
		std::priority_queue<int, std::vector<int>, std::less<int>> left_set;
		std::priority_queue<int, std::vector<int>, std::greater<int>> right_set;
		while(--seq_length)
		{
			seq = ((long long)seq * seq_a + seq_b) % seq_mod;
			
			if( left_set.size() == right_set.size() )
			{
				if( seq >= mid )
					right_set.push(seq);
				else
				{
					int lmax = left_set.top();
					if( seq >= lmax )
					{
						right_set.push(mid);
						mid = seq;
					}
					else
					{
						right_set.push(mid);
						left_set.pop();
						left_set.push(seq);
						mid = lmax;
					}
				}
			}
			else // left_queue.size() < right_queue.size()
			{
				if( seq <= mid )
					left_set.push(seq);
				else
				{
					int rmin = right_set.top();
					if( seq <= rmin )
					{
						left_set.push(mid);
						mid = seq;
					}
					else
					{
						left_set.push(mid);
						right_set.pop();
						right_set.push(seq);
						mid = rmin;
					}
				}
			}

			sum = (sum+mid) % seq_mod;
		}

		printf("%d\n", sum);
	}

	return 0;
}
