#include <stdio.h>
#include <vector>

namespace my
{
#ifdef __GNUC__
#define getchar getchar_unlocked
#endif

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
}

struct info
{
	int year, rain;
	int continuous;
	info* prevhigh;
	info* nexthigh;
} infos[50000];
std::vector<int> maxrain;

info* get_info( int begin, int end, int year );
bool maxrain_exist( int y, int x );
int main( int argc, char** argv )
{
	int num_info;
	my::cin >> num_info;

	int continuous = 0;
	for( int i = 0; i < num_info; ++i )
	{
		int year, rain;
		my::cin >> year >> rain;

		if( i > 0 && year != infos[i-1].year+1 )
			++continuous;

		infos[i].year = year;
		infos[i].rain = rain;
		infos[i].continuous = continuous;
		infos[i].prevhigh = i == 0 ? NULL : &infos[i-1];

		while( infos[i].prevhigh )
		{
			if( infos[i].prevhigh->rain >= infos[i].rain )
				break;

			infos[i].prevhigh = infos[i].prevhigh->prevhigh;
		}

		if( rain == 1000000000 )
			maxrain.push_back(year);
	}
	for( int i = num_info-1; i >= 0; --i )
	{
		infos[i].nexthigh = i == num_info-1 ? NULL : &infos[i+1];
		while( infos[i].nexthigh )
		{
			if( infos[i].nexthigh->rain >= infos[i].rain )
				break;
			
			infos[i].nexthigh = infos[i].nexthigh->nexthigh;
		}
	}

	int num_talk;
	my::cin >> num_talk;

	for( int i = 0; i < num_talk; ++i )
	{
		int yyear, xyear;
		my::cin >> yyear >> xyear;

		info* y = get_info( 0, num_info, yyear );
		info* x = get_info( 0, num_info, xyear );

		if( y && x && y->rain >= x->rain && ( x->prevhigh == NULL || x->prevhigh->year <= y->year ) )
			printf( y->continuous == x->continuous ? "true\n" : "maybe\n" );
		else if( !y && x && ( x->prevhigh == NULL || x->prevhigh->year <= yyear ) )
			printf("maybe\n");
		else if( y && !x && ( y->nexthigh == NULL || y->nexthigh->year >= xyear ) )
			printf("maybe\n");
		else if( !y && !x && !maxrain_exist(yyear, xyear) )
			printf("maybe\n");
		else
			printf("false\n");
	}

	return 0;
}

info* get_info( int begin, int end, int year )
{
	if( begin >= end )
		return NULL;
	
	int mid = (begin+end)/2;
	if( infos[mid].year == year )
		return &infos[mid];
	else if( infos[mid].year < year )
		return get_info( mid+1, end, year );
	else
		return get_info( begin, mid, year );
}

bool maxrain_exist( int y, int x )
{
	for( int year : maxrain )
	{
		if( year > y && year < x )
			return true;
	}

	return false;
}
