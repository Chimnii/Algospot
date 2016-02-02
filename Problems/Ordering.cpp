#include <stdio.h>
#include <vector>

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
}

using namespace std;
typedef pair<int,int> rule;

void find_order( int num_word, vector<rule>& rules, vector<int>& orders );
int main( int argc, char** argv )
{
	int num_testcase;
	my::cin >> num_testcase;

	while( num_testcase-- )
	{
		int num_word, num_rule;
		my::cin >> num_word >> num_rule;

		vector<rule> rules;
		for( int i = 0; i < num_rule; ++i )
		{
			char rule[3];
			my::cin >> rule;
			rules.push_back(make_pair(rule[0]-'A', rule[1]-'A'));
		}

		vector<int> orders;
		find_order(num_word, rules, orders);

		for( auto i : orders )
			printf("%c", i+'A');
		printf("\n");
	}

	return 0;
}

bool is_first( int index, vector<rule>& rules )
{
	for( auto rule : rules )
	{
		if( rule.second == index )
			return false;
	}

	return true;
}

void remove_rule( int index, vector<rule>& rules )
{
	for( int i = rules.size()-1; i >= 0; --i )
	{
		if( rules[i].first == index || rules[i].second == index )
			rules.erase(rules.begin()+i);
	}
}

void find_order( int num_word, vector<rule>& rules, vector<int>& orders )
{
	bool finded['Z'-'A'+1] = {0,};

	int index = 0;
	while( index < num_word )
	{
		if( finded[index] )
		{
			++index;
		}
		else if( is_first(index, rules) )
		{
			orders.push_back(index);
			remove_rule(index, rules);
			finded[index] = true;
			index = 0;
		}
		else
		{
			++index;
		}
	}
}
