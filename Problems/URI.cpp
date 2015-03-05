#include <iostream>
#include <string>

const std::string SpecialCharacter[7] = { " ", "!", "$", "%", "(", ")", "*" };
const std::string EncodedString[7] = { "%20", "%21", "%24", "%25", "%28", "%29", "%2a" };


int main( int argc, char** argv )
{
	int testCase;
	std::cin >> testCase;

	while( testCase-- )
	{
		std::string uri;
		std::cin >> uri;

		size_t prev = 0;
		while(true)
		{
			size_t pos = uri.find( "%", prev );
			if( pos == std::string::npos )
				break;

			for( int i = 0; i < 7; ++i )
			{
				if( EncodedString[i] == uri.substr( pos, EncodedString[i].length() ) )
				{
					uri.replace( pos, EncodedString[i].length(), SpecialCharacter[i] );
					break;
				}
			}
			prev = pos + 1;
		}

		std::cout << uri << std::endl;
	}

	return 0;
}