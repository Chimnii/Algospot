#include <iostream>
#include <string>
#include <algorithm>

enum EOperator { NONE, PLUS, MINUS, MULTIPLY };
std::string NUMBER[11] = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten" };

int getNumber( std::string str )
{
	std::sort( str.begin(), str.end() );

	for( int i = 0 ; i < 11; ++i )
	{
		if( NUMBER[i] == str )
			return i;
	}

	return -1;
}

EOperator getOperator( const std::string& op )
{
	if( op == "+" )
		return PLUS;
	else if( op == "-" )
		return MINUS;
	else if( op == "*" )
		return MULTIPLY;
	else
		return NONE;
}

int calc( int left, int right, EOperator op )
{
	switch( op )
	{
	case PLUS: return left + right; break;
	case MINUS: return left - right; break;
	case MULTIPLY: return left * right; break;
	}

	return -1;
}

int main( int argc, char** argv )
{
	int testCase;
	std::cin >> testCase;

	for( int i = 0 ; i < 11; ++i )
	{
		std::sort( NUMBER[i].begin(), NUMBER[i].end() );
	}

	while( testCase-- )
	{
		std::string left, right, op, eq, answer;
		std::cin >> left >> op >> right >> eq >> answer;

		int result = calc( getNumber( left ), getNumber( right ), getOperator( op ) );
		if( result >= 0 && result <= 10 && result == getNumber( answer ) )
			std::cout << "Yes" << std::endl;
		else
			std::cout << "No" << std::endl;
	}
	
	return 0;
}