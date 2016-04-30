#include <stdio.h>
#include <string>
#include <queue>

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

	inline bool is_char( char c ){ return ( c > ' '  ); }
	inline istream& operator>>( istream& in, char& out )
	{
		char c;
		while( c = getchar() ){ if( is_char(c) ){ out = c; break; } }
		return in;
	}
}

int members[10000];
int teamids[10000], teamops[10000], team_count;

int make_newteams()
{
	teamops[team_count] = -1;
	return teamids[team_count] = team_count++;
}

int get_teamid( int index )
{
	if( teamids[index] == index )
		return teamids[index];
	
	return teamids[index] = get_teamid(teamids[index]);
}
int get_teamop( int index )
{
	return teamops[index] = get_teamid(teamops[index]);
}
void set_teamid( int team, int id ){ teamids[team] = id; }
void set_teamop( int team, int opid ){ teamops[team] = opid; }

bool ack( int mem1, int mem2 );
bool dis( int mem1, int mem2 );
int get_maxparty( int num_member );
int main( int argc, char** argv )
{
	int num_testcase;
	my::cin >> num_testcase;

	while( num_testcase-- )
	{
		int num_member, num_comment;
		my::cin >> num_member >> num_comment;

		team_count = 0;
		for( int i = 0; i < num_member; ++i )
		{
			members[i] = -1;
		}

		bool correction = true;
		for( int i = 1; i <= num_comment; ++i )
		{
			char type;
			int mem1, mem2;
			my::cin >> type >> mem1 >> mem2;

			if( type == 'A' )
			{
				correction = ack(mem1, mem2);
			}
			else
			{
				correction = dis(mem1, mem2);
			}

			if( !correction )
			{
				printf("CONTRADICTION AT %d\n", i);
				while( ++i <= num_comment ) my::cin >> type >> mem1 >> mem2;
				break;
			}
		}

		if( correction )
		{
			printf("MAX PARTY SIZE IS %d\n", get_maxparty(num_member));
		}

	}

	return 0;
}

bool ack( int mem1, int mem2 )
{
	if( members[mem1] == -1 && members[mem2] == -1 )
	{
		int team = make_newteams();
		int opteam = make_newteams();

		set_teamop( team, opteam );
		set_teamop( opteam, team);
		members[mem1] = team;
		members[mem2] = team;
	}
	else if( members[mem2] == -1 )
	{
		members[mem2] = get_teamid( members[mem1] );
	}
	else if( members[mem1] == -1 )
	{
		members[mem1] = get_teamid( members[mem2] );
	}
	else
	{
		int team1 = get_teamid( members[mem1] );
		int team2 = get_teamid( members[mem2] );
		int team1op = get_teamop(team1);
		int team2op = get_teamop(team2);

		if( team1op == team2 )
			return false;

		set_teamid( team2, team1 );
		set_teamid( team2op, team1op );
	}

	return true;
}

bool dis( int mem1, int mem2 )
{
	if( members[mem1] == -1 && members[mem2] == -1 )
	{
		int team = make_newteams();
		int opteam = make_newteams();

		set_teamop( team, opteam );
		set_teamop( opteam, team );
		members[mem1] = team;
		members[mem2] = opteam;
	}
	else if( members[mem2] == -1 )
	{
		members[mem2] = get_teamop( members[mem1] );
	}
	else if( members[mem1] == -1 )
	{
		members[mem1] = get_teamop( members[mem2] );
	}
	else
	{
		int team1 = get_teamid( members[mem1] );
		int team2 = get_teamid( members[mem2] );
		int team1op = get_teamop(team1);
		int team2op = get_teamop(team2);

		if( team1 == team2 )
			return false;

		set_teamid( team2op, team1 );
		set_teamid( team1op, team2 );
		set_teamop( team1, team2 );
		set_teamop( team2, team1 );
	}

	return true;
}

int get_maxparty( int num_member )
{
	static std::queue<std::pair<int,int>> team_queue;
	static bool team_checked[10000];
	static int team_member_count[10000];

	std::queue<std::pair<int,int>>().swap(team_queue);
	for( int i = 0; i < team_count; ++i )
	{
		team_checked[i] = false;
		team_member_count[i] = 0;
	}

	int non_team_members = 0;
	for( int i = 0; i < num_member; ++i )
	{
		if( members[i] == -1 )
		{
			++non_team_members;
			continue;
		}

		int teamid = get_teamid( members[i] );
		int teamop = get_teamop(teamid);

		if( !team_checked[teamid] )
		{
			team_queue.push(std::make_pair(teamid, teamop));
			team_checked[teamid] = true;
			team_checked[teamop] = true;
		}

		team_member_count[teamid]++;
	}

	int max_count = non_team_members;
	while( team_queue.size() > 0 )
	{
		auto team_pair = team_queue.front(); team_queue.pop();
		max_count += std::max( team_member_count[team_pair.first], team_member_count[team_pair.second] );
	}

	return max_count;
}

/*
4 4 ACK 0 1 ACK 1 2 DIS 1 3 ACK 2 0
100 4 ACK 0 1 ACK 1 2 ACK 2 3 ACK 3 4
3 4 ACK 0 1 ACK 1 2 DIS 2 0 ACK 1 0
8 6 DIS 0 1 ACK 1 2 ACK 1 4 DIS 4 3 DIS 5 6 ACK 5 7
10 3 DIS 0 1 DIS 2 3 ACK 0 2
*/