#include <stdio.h>
#include <vector>
#include <set>

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

int jumps[1000];
bool checked[1000];
std::set<int> adjs[1000];

int calc_camera( int num_gallery );
int main( int argc, char** argv )
{
	int num_testcase;
	my::cin >> num_testcase;

	while( num_testcase-- )
	{
		int num_gallery, num_edge;
		my::cin >> num_gallery >> num_edge;

		for( int i = 0; i < num_gallery; ++i )
		{
			jumps[i] = i+1;
			checked[i] = false;
			adjs[i].clear();
		}
		jumps[num_gallery-1] = 0;

		for( int i = 0; i < num_edge; ++i )
		{
			int gal1, gal2;
			my::cin >> gal1 >> gal2;
			adjs[gal1].insert(gal2);
			adjs[gal2].insert(gal1);
		}

		int minimum_cam = calc_camera(num_gallery);
		printf("%d\n", minimum_cam);
	}

	return 0;
}

void remove_gallery( int target )
{
	for( int next : adjs[target] )
	{
		adjs[next].erase(target);
	}
}

int set_camera( int target )
{
	int check = 0;
	for( int next : adjs[target] )
	{
		adjs[next].erase(target);
		if( adjs[next].size() == 1 )
		{
			remove_gallery(next);
		}
		if( !checked[next] )
		{
			checked[next] = true;
			++check;
		}
	}
	adjs[target].clear();

	if( !checked[target] )
	{
		checked[target] = true;
		++check;
	}

	return check;
}

int calc_camera( int num_gallery )
{
	int camera_count = 0;
	int remain_gallery = num_gallery;

	int prev = num_gallery-1, current = 0;
	while(remain_gallery)
	{
		if( checked[current] )
		{
			current = jumps[current];
			continue;
		}
		else
		{
			jumps[prev] = current;
			prev = current;
		}

		if( adjs[current].size() == 0 )
		{
			checked[current] = true;
			--remain_gallery;
			++camera_count;
		}
		else if( adjs[current].size() == 1 )
		{
			int next = *adjs[current].begin();
			remain_gallery -= set_camera(next);
			++camera_count;
		}

		current = jumps[current];
	}

	return camera_count;
}
