#include <iostream>
#include <cmath>

int main( int argc, char** argv )
{
	int numTestCase;
	std::cin >> numTestCase;
	
	while( numTestCase-- )
	{
		long long playCount, winCount;
		std::cin >> playCount >> winCount;

		long long winRatio = winCount * 100 / playCount;
		if( winRatio >= 99 )
		{
			std::cout << -1 << std::endl;
		}
		else
		{	
			long long needCount = ( ( winRatio + 1 ) * playCount - winCount * 100 ) / ( 99 - winRatio );
			
			if( ( winCount + needCount ) * 100 / ( playCount + needCount ) == winRatio )
				++needCount;

			std::cout << needCount << std::endl;
		}
	}

	return 0;
}