#include <iostream>

inline int max( int a, int b )
{
	return a > b ? a : b;
}

int main( int argc, char** argv )
{
	int testCase;
	std::cin >> testCase;

	while( testCase-- )
	{
		int n, length;
		std::cin >> length;

		int diamond[2][102] = {0,};

		for( int i=1; i<=length; ++i )
		{
			for( int j=1; j<=length; ++j )
				diamond[i%2][j] = 0;
			for( int j=1; j<=i; ++j )
			{
				std::cin >> n;
				diamond[i%2][j] = n + max( diamond[(i+1)%2][j-1], diamond[(i+1)%2][j] );
			}
		}
		for( int i=length-1; i>=1; --i )
		{
			for( int j=1; j<=length; ++j )
				diamond[i%2][j] = 0;
			for( int j=1; j<=i; ++j )
			{
				std::cin >> n;
				diamond[i%2][j] = n + max( diamond[(i+1)%2][j], diamond[(i+1)%2][j+1] );
			}
		}

		std::cout << diamond[1][1] << std::endl;
	}

	return 0;
}