#include <iostream>

typedef unsigned long DWORD;

int main( int argc, char** argv )
{
	int testCase;
	std::cin >> testCase;

	const DWORD digit = 0x000000FF;

	while( testCase-- )
	{
		DWORD before = 0, after = 0;
		std::cin >> before;

		for( int i=0; i<4; ++i )
		{
			after = after << 8;
			after += before & digit;
			before = before >> 8;
		}

		std::cout << after << std::endl;
	}
}