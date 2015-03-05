#include <iostream>
#include <iomanip>

double calcMinimumDist( double dist[8][8], int city, bool visit[8], int current )
{
	double minimumDistance = -1;
	for( int i = 0; i < city; ++i )
	{
		if( visit[i] == false )
		{
			visit[i] = true;
			double distance = calcMinimumDist( dist, city, visit, i ) + ( current == -1 ? 0 : dist[current][i] );
			minimumDistance = minimumDistance == -1 ? distance : std::min( minimumDistance, distance );
			visit[i] = false;
		}
	}

	if( minimumDistance == - 1)
		minimumDistance = 0;

	return minimumDistance;
}

int main( int argc, char ** argv )
{
	int testCase;
	std::cin >> testCase;

	while( testCase-- )
	{
		int city;
		std::cin >> city;

		double dist[8][8] = {0,};
		for( int i = 0; i < city; ++i )
		{
			for( int j = 0; j < city; ++j )
			{
				std::cin >> dist[i][j];
			}
		}

		bool visit[8] = {0,};
		std::cout << std::fixed << std::setprecision(10) << calcMinimumDist( dist, city, visit, -1 ) << std::endl;
	}

	return 0;
}