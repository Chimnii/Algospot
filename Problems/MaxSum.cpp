#include <iostream>

int main( int argc, char** argv )
{
	int numTestCase;
	std::cin >> numTestCase;

	while( numTestCase-- )
	{
		int length;
		std::cin >> length;

		int currSum = 0;
		int maxSum = 0;
		int sequence[100000];
		for( int i = 0; i < length; ++i )
		{
			std::cin >> sequence[i];
			if( sequence[i] >= 0 )
			{
				currSum += sequence[i];

				if( currSum > maxSum )
				{
					maxSum = currSum;
				}
			}
			else
			{
				if( sequence[i] + currSum >= 0 )
				{
					currSum += sequence[i];
				}
				else
				{
					currSum = 0;
				}
			}
		}

		std::cout << maxSum << std::endl;
	}

	return 0;
}