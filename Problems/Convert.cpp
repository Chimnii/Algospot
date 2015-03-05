#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstring>

const char SCALE[4][3][10] = { {"kg", "2.2046", "lb"}, {"lb", "0.4536", "kg"}, {"l", "0.2642", "g"}, {"g", "3.7854", "l"} };

int main( int argc, char** argv )
{
	int testCase;
	std::cin >> testCase;

	for( int i = 1; i <= testCase; ++i )
	{
		double n;
		char unit[3];
		std::cin >> n >> unit;

		for( int j = 0; j < 4; ++j )
		{
			if( strcmp( unit, SCALE[j][0] ) == 0 )
			{
				double converted = n * atof( SCALE[j][1] );
				std::cout << i << " " << std::fixed << std::setprecision(4) << converted << " " << SCALE[j][2] << std::endl;
				break;
			}
		}
	}

	return 0;
}