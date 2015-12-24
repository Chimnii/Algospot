#include <stdio.h>
#include <string>
#include <set>
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
	inline istream& operator>>( istream&in, std::string& out )
	{
		static char temp[32];
		operator>>( in, temp );
		out = temp;
		return in;
	}
}

using namespace std;

struct alphabet
{
	char ch;
	set<char> parents;
	bool has_parent(char p);
};
alphabet alphabets['z'+1];

void clear();
bool make_list( const vector<string>& dictionary );
void print_list();

int main( int argc, char** argv )
{
	int num_testcase;
	my::cin >> num_testcase;

	while( num_testcase-- )
	{
		int num_word;
		my::cin >> num_word;
		
		vector<string> dictionary;
		for( int i = 0 ; i < num_word; ++i )
		{
			string word;
			my::cin >> word;
			dictionary.push_back(word);
		}

		clear();
		if( make_list(dictionary) )
		{
			print_list();
		}
		else
		{
			printf("INVALID HYPOTHESIS\n");
		}
	}

	return 0;
}

bool alphabet::has_parent( char p )
{
	return parents.find(p) != parents.end();
}

void clear()
{
	for( int i = 'a'; i <= 'z'; ++i )
	{
		alphabets[i].ch = i;
		alphabets[i].parents.clear();
	}
}

bool add_pair( char p, char c )
{
	if( alphabets[p].has_parent(c) )
	{
		return false;
	}

	alphabets[c].parents.insert(p);
	return true;
}

bool make_list( const vector<string>& dictionary )
{
	if( dictionary.size() <= 1 )
		return true;

	auto prev = dictionary.begin();
	auto curr = prev + 1;
	while( curr != dictionary.end() )
	{
		for( size_t i = 0; i < std::min(prev->length(), curr->length()); ++i )
		{
			char p = prev->at(i);
			char c = curr->at(i);
			if( p != c )
			{
				if( !add_pair(p, c) )
					return false;
				break;
			}
		}

		++prev;
		++curr;
	}

	return true;
}

void print_list()
{
	int printed_count = 0;
	bool printed['z'+1] = {0,};
	while(printed_count < 26)
	{
		for( int i = 'a'; i <= 'z'; ++i )
		{
			if( printed[i] )
				continue;

			bool is_first = true;
			for( auto parent : alphabets[i].parents )
			{
				if( !printed[parent] )
					is_first = false;
			}

			if( is_first )
			{
				printf("%c", i);
				printed[i] = true;
				printed_count++;
			}
		}
	}

	printf("\n");
}

/* test-case
100
6
aa
ba
bcc
bce
dd
de
3
ba
aa
ab
5
gg
kia
lotte
lg
hanhwa
6
dictionary
english
is
ordered
ordinary
this
*/
/*
INVALID HYPOTHESIS
ogklhabcdefijmnpqrstuvwxyz
abcdefghijklmnopqrstuvwxyz
*/