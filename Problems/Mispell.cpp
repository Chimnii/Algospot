#include <iostream>
#include <string>

int main()
{
	int testCase;
	std::cin >> testCase;

	for( int i = 1; i <= testCase; ++i )
	{
		int n;
		std::string str;
		std::cin >> n >> str;

		str.erase( n-1, 1 );
		std::cout << i << " " << str << std::endl;
	}

	return 0;
}