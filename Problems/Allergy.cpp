#include <stdio.h>
#include <string>
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

	inline bool is_char( char c ){ return ( c > ' '  ); }
	inline istream& operator>>( istream& in, char* out )
	{
		char c;
		while( c = getchar() ){ if( is_char(c) ){ *out = c; ++out; break; } }
		while( c = getchar() ){ if( !is_char(c) ) break; *out = c; ++out; }
		*out = 0;
		return in;
	}

	inline istream& operator>>( istream& in, char& out )
	{
		char c;
		while( c = getchar() ){ if( is_char(c) ){ out = c; break; } }
		return in;
	}

	inline istream& operator>>( istream&in, std::string& out )
	{
		static char temp[32];
		operator>>( in, temp );
		out = temp;
		return in;
	}

	inline void calc_min( int& min, int value ){ if( min > value ) min = value; }
}

using namespace std;

const int max_friends = 50;
const int max_foods = 50;
const int max_unallergied_food = 10000;

bool like_table[max_friends][max_foods];
bool friend_table[max_friends];
bool food_table[max_friends];
int num_friend, num_food;
int min_unallergied_food;

int get_name_index( string* name_table, const string& name);
void get_minimum_unallergied_foodset( int checked_food );
int main( int argc, char** argv )
{
	int num_testcase;
	my::cin >> num_testcase;

	while( num_testcase-- )
	{
		min_unallergied_food = max_unallergied_food;

		my::cin >> num_friend >> num_food;
		for( int i = 0; i < num_friend; ++i ) friend_table[i] = false;
		for( int i = 0; i < num_food; ++i ) food_table[i] = false;

		string name_table[max_friends];
		for( int i = 0; i < num_friend; ++i )
		{
			my::cin >> name_table[i];
		}

		for( int d = 0; d < num_food; ++d )
		{
			int likes;
			my::cin >> likes;

			for( int r = 0; r < num_friend; ++r )
			{
				like_table[r][d] = false;
			}
			for( int r = 0; r < likes; ++r )
			{
				string name;
				my::cin >> name;
				int ifriend = get_name_index(name_table, name);
				like_table[ifriend][d] = true;
			}
		}

		get_minimum_unallergied_foodset(0);
		printf("%d\n", min_unallergied_food);
	}

	return 0;
}

int get_name_index( string* name_table, const string& name)
{
	for( int r = 0; r < num_friend; ++r )
		if( name_table[r] == name )
			return r;
	return -1;
}

bool is_end()
{
	for( int r = 0; r < num_friend; ++r )
		if( !friend_table[r] )
			return false;
	return true;
}

void check_food( int d, vector<int>& new_checked_friend, vector<int>& new_checked_food )
{
	for( int r = 0; r < num_friend; ++r )
	{
		if( friend_table[r] ) continue;

		if( like_table[r][d] )
		{
			friend_table[r] = true;
			new_checked_friend.push_back(r);
		}
	}

	food_table[d] = true;
	new_checked_food.push_back(d);
}

void rollback_food( vector<int>& new_checked_friend, vector<int>& new_checked_food)
{
	for( auto rit = new_checked_friend.begin(); rit != new_checked_friend.end(); ++rit )
	{
		friend_table[*rit] = false;
	}

	for( auto dit = new_checked_food.begin(); dit != new_checked_food.end(); ++dit )
	{
		food_table[*dit] = false;
	}
}

void get_minimum_unallergied_foodset( int checked_food )
{
	if( checked_food >= min_unallergied_food )
		return;
	
	if( is_end() )
	{
		my::calc_min( min_unallergied_food, checked_food );
		return;
	}

	int min_like_food = max_foods;
	int current_friend;
	for( int r = 0; r < num_friend; ++r )
	{
		if( friend_table[r] ) continue;

		int like_food = 0;
		for( int d = 0; d < num_food; ++d )
		{
			if( food_table[d] ) continue;

			like_food += like_table[r][d] ? 1 : 0;
		}

		if( like_food < min_like_food )
		{
			min_like_food = like_food;
			current_friend = r;
		}
	}

	if( min_like_food < 1 )
	{
		printf("error\n");
		return;
	}
	else if( min_like_food == 1 )
	{
		for( int d = 0; d < num_food; ++d )
		{
			if( food_table[d] ) continue;

			if( like_table[current_friend][d] )
			{
				vector<int> new_checked_friend, new_checked_food;
				check_food(d, new_checked_friend, new_checked_food);
				break;
			}
		}

		return get_minimum_unallergied_foodset(checked_food+1);
	}
	else
	{
		for( int d = 0; d < num_food; ++d )
		{
			if( food_table[d] ) continue;

			if( like_table[current_friend][d] )
			{
				vector<int> new_checked_friend, new_checked_food;
				check_food(d, new_checked_friend, new_checked_food);
				get_minimum_unallergied_foodset(checked_food+1);
				rollback_food(new_checked_friend, new_checked_food);
			}
		}

		return;
	}
}

/* test-case
4 6
cl bom dara minzy
2 dara minzy
2 cl minzy
2 cl dara
1 cl
2 bom dara
2 bom minzy
10 7
a b c d e f g h i j
6 a c d h i j
3 a d i
7 a c f g h i j
3 b d g
5 b c f h i
4 b e g j
5 b c g h i
4 5
a b c d
1 a
1 b
2 a b
2 b c
3 b c d
*/
/*
2
3
2
*/
