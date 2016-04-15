#include <stdio.h>
#include <set>
#include <vector>

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
	inline void calc_max( int& max, int value ){ if( max < value ) max = value; }
}

int used_set;
std::set<int> sets[100001];
std::set<int>* get_newset();

int max_connected_size;
std::set<int>* connected[100001];

void connect( int p1, int p2 );
int main( int argc, char** argv )
{
	int num_testcase;
	my::cin >> num_testcase;

	while( num_testcase-- )
	{
		int num_point, num_line;
		my::cin >> num_point >> num_line;

		used_set = 0;
		max_connected_size = 0;
		for( int i = 1; i <= num_point; ++i )
		{
			connected[i] = NULL;
		}

		for( int i = 1; i <= num_line; ++i )
		{
			int p1, p2;
			my::cin >> p1 >> p2;

			connect(p1, p2);
		}

		printf("%d\n", max_connected_size);
	}

	return 0;
}

std::set<int>* get_newset()
{
	sets[used_set].clear();
	return &sets[used_set++];
}

void connect( int p1, int p2 )
{
	std::set<int>* set;
	if( !connected[p1] && !connected[p2] )
	{
		set = get_newset();
		set->insert(p1);
		set->insert(p2);
		connected[p1] = set;
		connected[p2] = set;
	}
	else if( connected[p1] && connected[p2] )
	{
		if( connected[p1] == connected[p2] )
			return;

		int large = connected[p1]->size() > connected[p2]->size() ? p1 : p2;
		int small = connected[p1]->size() > connected[p2]->size() ? p2 : p1;

		set = connected[large];

		auto old = connected[small];
		for( int val : *connected[small] )
		{
			set->insert(val);
			connected[val] = set;
		}
		old->clear();
	}
	else
	{
		int conn = connected[p1] ? p1 : p2;
		int disconn = connected[p1] ? p2 : p1;

		set = connected[conn];
		set->insert(disconn);
		connected[disconn] = set;
	}

	my::calc_max(max_connected_size, set->size());
}

/*
bool processed[100001];
std::vector<int> connected[100001];

int pop( std::set<int>& set );
int find( int start );
int main( int argc, char** argv )
{
	int num_testcase;
	my::cin >> num_testcase;

	while( num_testcase-- )
	{
		int num_point, num_line;
		my::cin >> num_point >> num_line;

		int max_connected_size = 0;
		for( int i = 1; i <= num_point; ++i )
		{
			processed[i] = false;
			connected[i].clear();
		}
		for( int i = 1; i <= num_line; ++i )
		{
			int p1, p2;
			my::cin >> p1 >> p2;
			connected[p1].push_back(p2);
			connected[p2].push_back(p1);
		}

		for( int i = 1; i <= num_point; ++i )
		{
			if( processed[i] ) continue;

			int connected_size = find(i);
			if( connected_size > max_connected_size )
				max_connected_size = connected_size;
		}

		printf("%d\n", max_connected_size);
	}

	return 0;
}

int pop( std::set<int>& set )
{
	int val = *set.begin();
	set.erase(set.begin());
	return val;
}

int find( int start )
{
	std::set<int> conn;
	conn.insert(start);
	processed[start] = true;

	int connected_size = 0;
	while( conn.size() > 0 )
	{
		int index = pop(conn);
		for( int val : connected[index] )
		{
			if( !processed[val] )
			{
				conn.insert(val);
				processed[val] = true;
			}
		}
		++connected_size;
	}

	return connected_size;
}
*/