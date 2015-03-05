#include <iostream>
#include <string>

int main( int argc, char** argv )
{
	int testCase;
	std::cin >> testCase;

	while( testCase-- )
	{
		std::string str;
		std::cin >> str;

		for( int i = 0; i < static_cast<int>(str.length()); i += 2 )
			std::cout << str.at(i);
		for( int i = 1; i < static_cast<int>(str.length()); i += 2 )
			std::cout << str.at(i);
		std::cout << std::endl;
	}

	return 0;
}