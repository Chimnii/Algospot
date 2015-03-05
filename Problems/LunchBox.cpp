#include <iostream>
#include <algorithm>

bool Compare( const std::pair<int, int>& a, const std::pair<int, int>& b )
{
	return a.second > b.second;
}

int main( int argc, char** argv )
{
	int numTestCase;
	std::cin >> numTestCase;

	std::pair<int, int> times[10000];
	while( numTestCase-- )
	{
		int numLunch;
		std::cin >> numLunch;

		for( int i = 0; i < numLunch; ++i ) std::cin >> times[i].first;
		for( int i = 0; i < numLunch; ++i ) std::cin >> times[i].second;
		std::sort( times, &times[numLunch], Compare );

		int maxTime = 0;
		int accumTime = 0;
		for( int i = 0; i < numLunch; ++i )
		{
			accumTime += times[i].first;
			int eatingTime = accumTime + times[i].second;
			if( maxTime < eatingTime )
				maxTime = eatingTime;
		}

		std::cout << maxTime << std::endl;
	}

	return 0;
}