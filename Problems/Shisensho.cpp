#include <iostream>
#include <vector>

struct Point
{
	char ch;
	int row, col;
	Point( char cc, int r, int c ) : ch(cc), row(r), col(c) {}
	bool operator==( const Point& other )
	{
		return row == other.row && col == other.col;
	}
};

struct Pair
{
	Point p1, p2;
	Pair( Point a, Point b ) : p1(a), p2(b) {}
	bool operator==( const Pair& other )
	{
		return ( p1 == other.p1 && p2 == other.p2 ) || ( p1 == other.p2 && p2 == other.p1 );
	}
};

int height, width;
char board[50][51];

void getSamePairs( std::vector<Pair>& samePairs )
{
	std::vector<Point> pointList;
	for( int i = 0; i < height; ++i )
	{
		for( int j = 0; j < width; ++j )
		{
			if( board[i][j] != '.' )
			{
				Point p( board[i][j], i, j );
				pointList.push_back(p);
			}
		}
	}

	for( std::vector<Point>::const_iterator it = pointList.begin(); it != pointList.end(); ++it )
	{
		for( std::vector<Point>::const_iterator it2 = it + 1; it2 != pointList.end(); ++it2 )
		{
			if( it->ch == it2->ch )
			{
				Pair p( *it, *it2 );
				samePairs.push_back(p);
			}
		}
	}
}

bool isEmptyLine( const Point& p1, const Point& p2 )
{
	if( p1.row == p2.row && p1.col == p2.col )
	{
		return true;
	}
	else if( p1.row == p2.row )
	{
		int min = p1.col > p2.col ? p2.col : p1.col;
		int max = p1.col > p2.col ? p1.col : p2.col;
		for( int j = min + 1; j < max; ++j )
		{
			if( board[p1.row][j] != '.' )
				return false;
		}
	}
	else if( p1.col == p2.col )
	{
		int min = p1.row > p2.row ? p2.row : p1.row;
		int max = p1.row > p2.row ? p1.row : p2.row;
		for( int i = min + 1; i < max; ++i )
		{
			if( board[i][p1.col] != '.' )
				return false;
		}
	}
	else
	{
		return false;
	}

	return true;
}

bool isValidConnected( const Pair& pair )
{
	const Point& p1 = pair.p1;
	const Point& p2 = pair.p2;

	for( int i = 0; i < height; ++i )
	{
		Point p11( board[i][p1.col], i, p1.col );
		Point p22( board[i][p2.col], i, p2.col );
		if( ( p11 == p1 || p11.ch == '.' ) && ( p22 == p2 || p22.ch == '.' ) && isEmptyLine( p1, p11 ) && isEmptyLine( p2, p22 ) && isEmptyLine( p11, p22 ) )
			return true;
	}

	for( int j = 0; j < width; ++j )
	{
		Point p11( board[p1.row][j], p1.row, j );
		Point p22( board[p2.row][j], p2.row, j );
		if( ( p11 == p1 || p11.ch == '.' ) && ( p22 == p2 || p22.ch == '.' ) && isEmptyLine( p1, p11 ) && isEmptyLine( p2, p22 ) && isEmptyLine( p11, p22 ) )
			return true;
	}

	return false;
}

int main( int argc, char** argv )
{
	int testCase;
	std::cin >> testCase;

	while( testCase-- )
	{
		std::cin >> height >> width;
		for( int i = 0; i < height; ++i )
		{
			std::cin >> board[i];
		}

		std::vector<Pair> samePairs;
		std::vector<Pair> answerPairs;

		getSamePairs( samePairs );
		for( std::vector<Pair>::const_iterator it = samePairs.begin(); it != samePairs.end(); ++it )
		{
			if( isValidConnected( *it ) )
				answerPairs.push_back( *it );
		}

		std::cout << static_cast<int>( answerPairs.size() ) << std::endl;
	}

	return 0;
}