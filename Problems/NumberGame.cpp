#include <iostream>
#include <algorithm>

int gameBoard[51];

int game( int result[2][51][51], bool recorded[2][51][51], const bool turn, const int left, const int right )
{
	bool& currentRecorded = recorded[turn ? 1 : 0][left][right];
	int& currentResult = result[turn ? 1 : 0][left][right];

	if( currentRecorded )
		return currentResult;

	if( right - left <= 0 ) // 게임 끝
	{
		currentRecorded = true;
		currentResult = 0;
		return currentResult;
	}
	else if( right - left == 1 ) // 마지막
	{
		currentRecorded = true;
		if( turn ) currentResult += gameBoard[left];
		else currentResult -= gameBoard[left];
		return currentResult;
	}

	int getLeft = game( result, recorded, !turn, left+1, right ) + gameBoard[left] * ( turn ? 1 : -1 );
	int getRight = game( result, recorded, !turn, left, right-1 ) + gameBoard[right-1] * ( turn ? 1 : -1 );
	int delLeft = game( result, recorded, !turn, left+2, right );
	int delRight = game( result, recorded, !turn, left, right-2 );

	currentRecorded = true;
	if( turn ) currentResult = std::max( getLeft, std::max( getRight, std::max( delLeft, delRight ) ) );
	else currentResult = std::min( getLeft, std::min( getRight, std::min( delLeft, delRight ) ) );
	return currentResult;
}

int main( int argc, char** argv )
{
	int testCase;
	std::cin >> testCase;

	while( testCase-- )
	{
		int length;
		std::cin >> length;

		for( int i=0; i<length; ++i )
		{
			std::cin >> gameBoard[i];
		}

		int result[2][51][51] = {0,};
		bool recorded[2][51][51] = {0,};


		std::cout << game( result, recorded, true, 0, length ) << std::endl;
	}

	return 0;
}