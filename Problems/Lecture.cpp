#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main( int argc, char** argv )
{
	int testCase;
	std::cin >> testCase;

	while( testCase -- )
	{
		std::string str;
		std::cin >> str;

		std::vector<std::string> strList( str.length() / 2 );
		for( int i = 0; i < static_cast<int>(strList.size()); ++i )
		{
			strList[i] = str.substr( i*2, 2 );
		}

		std::sort( strList.begin(), strList.end() );
		
		for( int i = 0; i < static_cast<int>(strList.size()); ++i )
		{
			std::cout << strList[i];
		}
		std::cout << std::endl;
	}

	return 0;
}