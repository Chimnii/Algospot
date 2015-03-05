#include <iostream>
#include <string>
#include <stack>

bool isOpenBracket( char c ){ return c == '(' || c == '{' || c == '['; }
bool isCloseBracket( char c ){ return c == ')' || c == '}' || c == ']'; }
bool isCorrectBrackets( char open, char close ){ return ( open == '(' && close == ')' ) || ( open == '{' && close == '}' ) || ( open == '[' && close == ']' ); }

int main( int argc, char** argv )
{
	int testCase;
	std::cin >> testCase;

	while( testCase-- )
	{
		std::string str;
		std::cin >> str;

		bool bCorrect = true;
		std::stack<char> stack;
		for( std::string::const_iterator it = str.begin(); it != str.end() && bCorrect; ++it )
		{
			if( isOpenBracket(*it) )
			{
				stack.push(*it);
			}
			else if( isCloseBracket(*it) )
			{
				if( stack.size() > 0 && isCorrectBrackets( stack.top(), *it ) )
					stack.pop();
				else
					bCorrect = false;
			}
		}

		if( bCorrect && stack.size() == 0 )
			std::cout << "YES" << std::endl;
		else
			std::cout << "NO" << std::endl;
	}

	return 0;
}