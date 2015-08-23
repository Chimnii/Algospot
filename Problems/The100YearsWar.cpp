#include <stdio.h>
#include <vector>

namespace my
{
	struct istream{};
	istream cin;

	inline bool is_num(char c){ return (c >= '0' && c <= '9'); }
	inline bool is_negative(char c){ return c == '-'; }
	inline istream& operator>>(istream& in,int& out)
	{
		char c; out = 0; bool neg = false;
		while(c = getchar()){ if(is_negative(c)){ neg = true; break; } if(is_num(c)){ out += (c-'0'); break; } }
		while(c = getchar()){ if(!is_num(c)) break; out *= 10; out += (c-'0'); }
		if(neg) out *= -1;
		return in;
	}

	inline bool is_char(char c){ return (c > ' '); }
	inline istream& operator>>(istream& in,char& out)
	{
		char c;
		while(c = getchar()){ if(is_char(c)){ out = c; break; } }
		return in;
	}
}

struct CNoble
{
	int id = 0;
	int branch_id = 0;
	int branch_key = -1;
	int index = -1;
	std::vector<int> childs;
	std::vector< std::vector<int> > revolts;

	bool isMultiChilds(){ return childs.size() > 1; }
};

CNoble nobles[50001];

void make_tree( int current_id, int current_branch_id, int current_branch_key, int current_index );
void set_revolt( int id );
bool is_ally( int id1, int id2 );

int main( int argc,char** argv )
{
	int num_testcase;
	my::cin >> num_testcase;

	while(num_testcase--)
	{
		int num_noble, num_sentence;
		my::cin >> num_noble >> num_sentence;

		for( int i = 0; i <= num_noble; ++i )
		{
			nobles[i].id = i;
			nobles[i].branch_id = 0;
			nobles[i].branch_key = -1;
			nobles[i].index = -1;
			nobles[i].childs.clear();
			//nobles[i].revolts.clear();
		}

		nobles[0].childs.push_back(1);
		nobles[0].childs.push_back(2);
		for( int i = 0; i < num_noble-2; ++i )
		{
			int parent, id;
			my::cin >> parent >> id;

			nobles[parent].childs.push_back(id);
		}

		make_tree( 0, 0, 0, 0 );
		
		for( int i = 0; i < num_sentence; ++i )
		{
			char type;
			my::cin >> type;

			int id, id2;
			if( type == 'T' )
			{
				my::cin >> id;
				set_revolt(id);
			}
			else if( type == 'Q' )
			{
				my::cin >> id >> id2;
				if( is_ally( id, id2 ) )
					printf("Ally\n");
				else
					printf("Enemy\n");
			}
		}
	}

	return 0;
}

void make_tree( int current_id, int current_branch_id, int current_branch_key, int current_index )
{
	CNoble& noble = nobles[current_id];
	
	noble.branch_id = current_branch_id;
	noble.branch_key = current_branch_key;
	noble.index = current_index;
	
	int num_child = noble.childs.size();
	if( num_child == 0 )
	{
		return;
	}
	else if( num_child == 1 )
	{
		make_tree( noble.childs[0], current_branch_id, current_branch_key, current_index+1 );
	}
	else
	{
		for( int i = 0; i < num_child; ++i )
		{
			make_tree( noble.childs[i], current_id, i, current_index+1 );
		}
	}
	
	if( num_child > 1 )
	{
		noble.revolts.clear();
		noble.revolts.resize(num_child);
	}
}

void set_revolt( int id )
{
	CNoble& noble = nobles[id];
	CNoble& branch = nobles[ noble.branch_id ];

	std::vector<int>& revolt_list = branch.revolts[noble.branch_key];
	for( auto it = revolt_list.begin(); it != revolt_list.end(); ++it ) // 여기와 get의 이터레이팅이 느릴 것 같아 map으로 바꿨는데 시간초과 나온다;
	{
		auto revolt_id = *it;
		if( nobles[revolt_id].index == noble.index )
		{
			revolt_list.erase(it);
			return;
		}
		else if( nobles[revolt_id].index > noble.index )
		{
			revolt_list.insert(it, id);
			return;
		}
	}

	revolt_list.push_back(id);
}

int get_enemy( int id )
{
	if( id == 1 )
		return 2;
	else if( id == 2 )
		return 1;
	else
	{
		printf("error!\n");
		return 1;
	}
}

void get_branch_revolt( int id, int current_id, int current_key, int& ret_revolt, int& ret_country )
{
	CNoble& noble = nobles[current_id];

	if( current_id == nobles[id].branch_id )
	{
		for( auto it = noble.revolts[current_key].begin(); it != noble.revolts[current_key].end(); ++it )
		{
			int revolt = *it;
			if( nobles[revolt].index <= nobles[id].index )
				ret_revolt++;
			else
				break;
		}
	}
	else
	{
		ret_revolt += noble.revolts[current_key].size();
	}

	if( current_id == 0 )
	{
		ret_country = current_key + 1;
	}
	else
	{
		get_branch_revolt( id, noble.branch_id, noble.branch_key, ret_revolt, ret_country );
	}
}

int get_country( int id )
{
	int num_revolt = 0, country = 0;
	get_branch_revolt( id, nobles[id].branch_id, nobles[id].branch_key, num_revolt, country );

	if( num_revolt % 2 == 0 )
		return country;
	else
		return get_enemy(country);
}

bool is_ally( int id1, int id2 )
{
	int country1 = get_country(id1);
	int country2 = get_country(id2);
	return country1 == country2;
}