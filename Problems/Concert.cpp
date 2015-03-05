#include <iostream>

int main( int argc, char** argv )
{
	int numTestCase;
	std::cin >> numTestCase;

	int volumes[50];
	while( numTestCase-- )
	{
		int numSong, volumeStart, volumeMax;
		std::cin >> numSong >> volumeStart >> volumeMax;

		for( int i = 0; i < numSong; ++i )
		{
			std::cin >> volumes[i];
		}

		int cases[2][1001] = {0,};
		cases[0][volumeStart] = 1;

		bool canNext = true;
		int curr, next;
		for( int vi = 0; vi < numSong && canNext; ++vi )
		{
			curr = vi%2;
			next = (vi+1)%2;
			canNext = false;
			for( int ci = 0; ci < volumeMax+1; ++ci )
			{
				if( cases[curr][ci] == 1 )
				{
					if( ci + volumes[vi] <= volumeMax )
					{
						cases[next][ ci + volumes[vi] ] = 1;
						canNext = true;
					}
					if( ci - volumes[vi] >= 0 )
					{
						cases[next][ ci - volumes[vi] ] = 1;
						canNext = true;
					}
					cases[curr][ci] = 0;
				}
			}
		}

		if( canNext )
		{
			for( int ci = volumeMax; ci >= 0; --ci )
			{
				if( cases[next][ci] != 0 )
				{
					std::cout << ci << std::endl;
					break;
				}
			}
		}
		else
		{
			std::cout << -1 << std::endl;
		}
	}

	return 0;
}