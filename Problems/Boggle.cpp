#include <iostream>

bool dp[7][7][10];
char board[7][7] = {0,};
char word[15] = {0,};

bool FindNext( int row, int col, int current )
{
	if( word[current] == 0 )
		return true;
	if( dp[row][col][current] == false )
		return false;

	for( int r = -1; r <= 1; ++r )
	{
		for( int c = -1; c <= 1; ++c )
		{
			if( !(r == 0 && c == 0)  && board[row+r][col+c] == word[current] )
			{
				if( FindNext( row+r, col+c, current+1 ) )
					return true;
			}
		}
	}

	dp[row][col][current] = false;

	return false;
}

bool Find()
{
	for( int i = 1; i <= 5; ++i )
	{
		for( int j = 1; j <= 5; ++j )
		{
			if( board[i][j] == word[0] )
			{
				if( FindNext( i, j, 1 ) )
					return true;
			}
		}
	}

	return false;
}

int main( int argc, char** argv )
{
	int numTestCase;
	std::cin >> numTestCase;
	
	while( numTestCase-- )
	{
		for( int i = 1; i <= 5; ++i )
			for( int j = 1; j <= 5; ++j )
				std::cin >> board[i][j];
		
		int numWord;
		std::cin >> numWord;

		while( numWord-- )
		{
			for( int i = 1; i <=5; ++i )
				for( int j = 1; j <= 5; ++j )
					for( int k = 0; k < 10; ++k )
						dp[i][j][k] = true;

			std::cin >> word;
			if( Find() )
			{
				std::cout << word << " YES" << std::endl;
			}
			else
			{
				std::cout << word << " NO" << std::endl;
			}
		}
	}

	return 0;
}