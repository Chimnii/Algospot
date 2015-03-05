#include <iostream>
#include <cmath>

struct CStone
{
	enum EStoneState
	{
		UNVISITED,
		VISITED,
		NOROUTE,
	};

	int x, y;
	int state;

	CStone() : x(0), y(0), state(UNVISITED) {}
	double GetDistance( const CStone& dest )
	{
		return std::sqrt( static_cast<double>( (x-dest.x)*(x-dest.x) + (y-dest.y)*(y-dest.y) ) );
	}
};

std::istream& operator>>( std::istream& in, CStone& point )
{
	in >> point.x;
	in >> point.y;
	return in;
}

bool CanRouteDest( CStone stones[100], const int numStone, const int jumpingDist, CStone& currentStone, CStone& destStone );

int main( int argc, char** argv )
{
	int numTestCase;
	std::cin >> numTestCase;

	while( numTestCase-- )
	{
		int jumpingDist;
		std::cin >> jumpingDist;

		CStone start, dest;
		std::cin >> start >> dest;

		int numStone;
		std::cin >> numStone;

		CStone stones[100];

		for( int i = 0; i < numStone; ++i )
		{
			std::cin >> stones[i];
		}

		std::cout << ( CanRouteDest( stones, numStone, jumpingDist, start, dest ) ? "YES" : "NO" ) << std::endl;
	}

	return 0;
}

bool CanRouteDest( CStone stones[100], const int numStone, const int jumpingDist, CStone& currentStone, CStone& destStone )
{
	currentStone.state = CStone::VISITED;

	if( currentStone.GetDistance( destStone ) <= jumpingDist )
		return true;

	bool canRoute = false;
	for( int i = 0; i < numStone; ++i )
	{
		if( stones[i].state == CStone::UNVISITED && currentStone.GetDistance( stones[i] ) <= jumpingDist )
		{
			canRoute = canRoute || CanRouteDest( stones, numStone, jumpingDist, stones[i], destStone );
		}

		if( canRoute )
			break;
	}

	if( canRoute )
	{
		return true;
	}
	else
	{
		currentStone.state = CStone::NOROUTE;
		return false;
	}
}