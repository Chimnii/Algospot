#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

struct CBase
{
	float x, y;
};

std::istream& operator>>( std::istream& in, CBase& base )
{
	in >> base.x;
	in >> base.y;
	return in;
}

namespace Bases
{
	std::vector<CBase> communicated;
	std::vector<CBase> uncommunicated;
	float communicatingDist;
}

void CalcCommunicatingDistance();
int main( int argc, char** argv )
{
	int numTestCase;
	std::cin >> numTestCase;

	while( numTestCase-- )
	{
		int numBase;
		std::cin >> numBase;

		Bases::communicated.clear();
		Bases::uncommunicated.clear();
		Bases::communicatingDist = 0;

		for( int i = 0; i < numBase; ++i )
		{
			CBase base;
			std::cin >> base;
			Bases::uncommunicated.push_back(base);
		}

		CalcCommunicatingDistance();

		std::cout << std::fixed << std::setprecision(2) << Bases::communicatingDist << std::endl;
	}

	return 0;
}

void CalcCommunicatingDistance()
{
	CBase base = *Bases::uncommunicated.rbegin();
	Bases::communicated.push_back( base );
	Bases::uncommunicated.pop_back();

	while( !Bases::uncommunicated.empty() )
	{
		std::vector<CBase>::iterator minimumBase;
		
		float minimumDist = 0;
		for( std::vector<CBase>::iterator uncommedIt = Bases::uncommunicated.begin(); uncommedIt != Bases::uncommunicated.end(); ++uncommedIt )
		{
			for( std::vector<CBase>::iterator commedIt = Bases::communicated.begin(); commedIt != Bases::communicated.end(); ++commedIt )
			{
				float dist = std::sqrt( std::pow( commedIt->x - uncommedIt->x, 2 ) + std::pow( commedIt->y - uncommedIt->y, 2 ) );
				if( minimumDist == 0 || dist < minimumDist )
				{
					minimumDist = dist;
					minimumBase = uncommedIt;
				}
			}
		}

		Bases::communicated.push_back( *minimumBase );
		Bases::uncommunicated.erase( minimumBase );
		Bases::communicatingDist = std::max( Bases::communicatingDist, minimumDist );
	}
}