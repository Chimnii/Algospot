#include <stdio.h>
#include <queue>
#include <limits>

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

int minimum_cost;
struct minimum_queue
{
public:
	void init( int range );
	void push( int n );
	int get_minimum();
private:
	std::queue<int> queue;
	std::deque<int> deque;
	int range;
} mqueue;

int main( int argc, char** argv )
{
	int num_testcase;
	my::cin >> num_testcase;

	while( num_testcase-- )
	{
		int num_fire, range;
		my::cin >> num_fire >> range;

		mqueue.init(range);
		minimum_cost = std::numeric_limits<int>::max();
		for( int i = 0; i < num_fire; ++i )
		{
			int cost;
			my::cin >> cost;
			
			cost = mqueue.get_minimum() + cost;
			mqueue.push(cost);
			if( i >= num_fire - range && minimum_cost > cost )
				minimum_cost = cost;
		}

		printf("%d\n", minimum_cost);
	}

	return 0;
}

void minimum_queue::init( int range )
{
	this->range = range;

	std::queue<int>().swap(queue);
	deque.clear();

	queue.push(0);
	deque.push_back(0);
}

void minimum_queue::push( int n )
{
	if( queue.size() == range )
	{
		int front = queue.front(); queue.pop();
		if( deque.front() == front )
			deque.pop_front();
	}

	queue.push(n);
	while( deque.size() > 0 && deque.back() > n )
		deque.pop_back();
	deque.push_back(n);
}

int minimum_queue::get_minimum()
{
	if( deque.size() == 0 )
		return 0;
	else
		return deque.front();
}
