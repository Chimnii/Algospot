#include <stdio.h>
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
}


typedef std::pair<int, int> potion;
potion potions[101];

inline int sigma_n( int a, int b )
{
	return (b*(b+1)-a*(a-1))/2;
}

inline void drink( int& sum, potion p, int d )
{
	std::div_t dv = std::div(d, p.second);
	sum += p.second * sigma_n(p.first-dv.quot+1, p.first);
	sum += dv.rem * (p.first-dv.quot);
}

int main( int argc, char** argv )
{
	int num_testcase;
	my::cin >> num_testcase;

	while( num_testcase-- )
	{
		int num_item, num_drink;
		my::cin >> num_item >> num_drink;

		potions[0].first = 0;
		potions[0].second = 0;
		for( int i = 1; i <= num_item; ++i )
		{
			my::cin >> potions[i].first;
			potions[i].second = 1;
		}
		std::sort(&potions[1], &potions[num_item+1]);

		int sum = 0;
		int i = num_item;
		while(i > 0 && num_drink > 0)
		{
			int maxd = (potions[i].first-potions[i-1].first)*potions[i].second;
			if( maxd <= num_drink )
			{
				drink(sum, potions[i], maxd);
				num_drink -= maxd;
				potions[i-1].second += potions[i].second;
			}
			else
			{
				drink(sum, potions[i], num_drink);
				num_drink = 0;
			}
			--i;
		}

		printf("%d\n", sum);
	}

	return 0;
}


/*
typedef std::pair<int, int> potion;
std::vector<potion> potions;

inline int sigma_n( int a, int b )
{
	return (b*(b+1)-a*(a-1))/2;
}

inline void drink( int& sum, potion p, int d )
{
	std::div_t dv = std::div(d, p.second);
	sum += p.second * sigma_n(p.first-dv.quot+1, p.first);
	sum += dv.rem * (p.first-dv.quot);
}

int main( int argc, char** argv )
{
	int num_testcase;
	my::cin >> num_testcase;

	while( num_testcase-- )
	{
		int num_item, num_drink;
		my::cin >> num_item >> num_drink;

		potions.clear();
		for( int i = 0; i < num_item; ++i )
		{
			potion p;
			my::cin >> p.first;
			p.second = 1;
			potions.push_back(p);
		}
		std::sort(potions.begin(), potions.end());

		int sum = 0;
		potion top, sec;
		while(potions.size() >= 2 && num_drink > 0)
		{
			top = *potions.rbegin(); potions.pop_back();
			sec = *potions.rbegin(); potions.pop_back();

			int maxd = (top.first-sec.first)*top.second;
			if( maxd <= num_drink )
			{
				drink(sum, top, maxd);
				num_drink -= maxd;

				sec.second += top.second;
				potions.push_back(sec);
			}
			else
			{
				drink(sum, top, num_drink);
				num_drink = 0;
			}
		}
		if(potions.size() > 0 && num_drink > 0)
		{
			top = *potions.rbegin();
			drink(sum, top, std::min(top.first*top.second, num_drink));
		}

		printf("%d\n", sum);
	}

	return 0;
}
*/