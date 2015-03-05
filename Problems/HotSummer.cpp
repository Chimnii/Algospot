#include <iostream>

int main( int argc, char** argv )
{
	int building;
	std::cin >> building;

	while( building-- )
	{
		int max;
		std::cin >> max;

		int sum = 0;
		for( int i = 0; i < 9; ++i )
		{
			int n;
			std::cin >> n;
			sum += n;
		}

		if( sum <= max )
			std::cout << "YES" << std::endl;
		else
			std::cout << "NO" << std::endl;
	}
}