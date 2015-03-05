#include <iostream>

int GetFillCase( bool board[22][22], const int height, const int width )
{
	// Base is unfilled case
	int numCase = 0;

	for( int h = 0; h < height; ++h )
	{
		for( int w = 0; w < width; ++w )
		{
			if( board[h][w] )
			{
				board[h][w] = false;

				if( board[h][w+1] && board[h+1][w] )
				{
					board[h][w+1] = false;
					board[h+1][w] = false;
					numCase += GetFillCase( board, height, width );
					board[h][w+1] = true;
					board[h+1][w] = true;
				}

				if( board[h][w+1] && board[h+1][w+1] )
				{
					board[h][w+1] = false;
					board[h+1][w+1] = false;
					numCase += GetFillCase( board, height, width );
					board[h][w+1] = true;
					board[h+1][w+1] = true;
				}

				if( board[h+1][w] && board[h+1][w+1] )
				{
					board[h+1][w] = false;
					board[h+1][w+1] = false;
					numCase += GetFillCase( board, height, width );
					board[h+1][w] = true;
					board[h+1][w+1] = true;
				}

				if( board[h+1][w-1] && board[h+1][w] )
				{
					board[h+1][w-1] = false;
					board[h+1][w] = false;
					numCase += GetFillCase( board, height, width );
					board[h+1][w-1] = true;
					board[h+1][w] = true;
				}

				board[h][w] = true;

				return numCase;
			}
		}
	}

	// All filled case
	return 1;
}

int main( int argc, char** argv )
{
	int numTestCase;
	std::cin >> numTestCase;

	while( numTestCase-- )
	{
		int height, width;
		std::cin >> height >> width;

		bool board[22][22] = {0,};
		for( int h = 0; h < height; ++h )
		{
			for( int w = 0; w < width; ++w )
			{
				char c;
				std::cin >> c;
				board[h][w] = ( c == '.' );
			}
		}

		std::cout << GetFillCase( board, height, width ) << std::endl;
	}

	return 0;
}