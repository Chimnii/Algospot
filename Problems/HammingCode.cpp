#include <iostream>

int main( int argc, char** argv )
{
	int testCase;
	std::cin >> testCase;

	while( testCase-- )
	{
		char code[8];
		std::cin >> code;
		for( int i = 0; i < 7; ++i )
			code[i] = code[i] - '0';

		int errorBit = ( code[0] ^ code[2] ^ code[4] ^ code[6] )
					+  ( code[1] ^ code[2] ^ code[5] ^ code[6] ) * 2
					+  ( code[3] ^ code[4] ^ code[5] ^ code[6] ) * 4;
		if( errorBit > 0 )
			code[ errorBit-1 ] = !code[ errorBit - 1 ];

		std::cout << static_cast<int>(code[2]) << static_cast<int>(code[4]) << static_cast<int>(code[5]) << static_cast<int>(code[6]) << std::endl;
	}

	return 0;
}