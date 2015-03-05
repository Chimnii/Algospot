#include <iostream>
#include <vector>
#include <algorithm>

int main( int argc, char** argv )
{
	int numTestCase;
	std::cin >> numTestCase;

	while( numTestCase-- )
	{
		int numMember;
		std::cin >> numMember;

		std::vector<int> males(numMember), females(numMember);

		for( int i = 0; i < numMember; ++i ) std::cin >> males[i];
		for( int i = 0; i < numMember; ++i ) std::cin >> females[i];

		std::sort( males.begin(), males.end() );
		std::sort( females.begin(), females.end() );

		int sum = 0;
		for( int i = 0; i < numMember; ++i )
			sum += std::abs( males[i] - females[i] );

		std::cout << sum << std::endl;
	}

	return 0;
}