#include <stdio.h>
#include <vector>
#include <cmath>

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
}


struct wall
{
	int x, y, r;
	int max_depth;
	wall* parent = nullptr;
	std::vector<wall*> childs;

	void clear();
	void add( wall* );
	bool include( wall* );
	void calc_max_depth();
};
wall walls[100];
wall dummy;

int max_distance;
int main( int argc, char** argv )
{
	int num_testcase;
	my::cin >> num_testcase;

	while( num_testcase-- )
	{
		int num_wall;
		my::cin >> num_wall;

		dummy.clear();
		for( int i = 0; i < num_wall; ++i )
		{
			walls[i].clear();
			my::cin >> walls[i].x >> walls[i].y >> walls[i].r;
			dummy.add(&walls[i]);
		}

		max_distance = 0;
		dummy.calc_max_depth();
		printf("%d\n", max_distance);
	}

	return 0;
}

void wall::clear()
{
	x = y = r = 0;
	max_depth = 0;
	parent = nullptr;
	childs.clear();
}

void wall::add( wall* wall )
{
	for( auto it = childs.begin(); it != childs.end(); ++it )
	{
		auto child = *it;

		if( child->include(wall) )
		{
			child->add(wall);
			return;
		}

		if( wall->include(child) )
		{
			childs.erase(it);
			wall->childs.push_back(child);
			child->parent = wall;
			break;
		}
	}

	childs.push_back(wall);
	wall->parent = this;
}

bool wall::include( wall* wall )
{
	return r - wall->r - sqrt((wall->x-x)*(wall->x-x)+(wall->y-y)*(wall->y-y)) >= 0;
}

void wall::calc_max_depth()
{
	if( childs.size() == 0 )
	{
		max_depth = 0;
	}
	else if( childs.size() == 1 )
	{
		childs[0]->calc_max_depth();

		max_depth = childs[0]->max_depth+1;
		my::calc_max( max_distance, childs[0]->max_depth );
	}
	else
	{
		int fst = 0, snd = 0;
		for( auto child : childs )
		{
			child->calc_max_depth();

			int depth = child->max_depth;
			if( depth > fst )
			{
				snd = fst;
				fst = depth;
			}
			else if( depth > snd )
			{
				snd = depth;
			}
		}

		max_depth = fst+1;
		my::calc_max( max_distance, fst+snd+2 );
	}
}

/*
10
3
5 5 15
5 5 10
5 5 5
8 
21 15 20 
15 15 10 
13 12 5 
12 12 3 
19 19 2 
30 24 5 
32 10 7 
32 9 4
*/