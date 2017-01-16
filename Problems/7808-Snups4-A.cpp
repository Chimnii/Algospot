#include <iostream>
#include <string>
#include <cstring>

int main()
{
	int keys[3000], length, width, height;
	char message[3000];
	char ciphers[3000];

	std::string in;
	while( std::getline(std::cin, in) )
	{
		if( in == "" )
			continue;

		strncpy( message, in.c_str(), in.length() );
		length = in.length();
		std::cin >> width;
		height = (length-1) / width + 1;

		for( int i = length; i <= width*height; ++i )
			message[i] = 0;

		for( int i = 0; i < width; ++i )
			std::cin >> keys[i];

		for( int i = 0; i < width; ++i )
		{
			int begin = (keys[i] - 1) * height;
			for( int j = 0; j < height; ++j )
			{
				ciphers[begin+j] = message[j*width+i]; 
			}
		}

		for( int i = 0; i < width*height; ++i )
		{
			if( ciphers[i] )
				std::cout << ciphers[i];
		}
		std::cout << std::endl;
	}

	return 0;
}
