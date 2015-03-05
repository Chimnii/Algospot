#include <iostream>
#include <string>
#include <stack>

bool isOpenParen( char c ){ return c == '(' || c == '{' || c == '[' || c == '<'; }
bool isCloseParen( char c ){ return c == ')' || c == '}' || c == ']' || c == '>'; }
char getPairParen( char c )
{
	switch(c)
	{
	case '(': return ')';
	case '{': return '}';
	case '[': return ']';
	case '<': return '>';
	case ')': return '(';
	case '}': return '{';
	case ']': return '[';
	case '>': return '<';
	}

	return 0;
}

int main( int argc, char** argv )
{
	int testCase;
	std::cin >> testCase;

	while( testCase-- )
	{
		std::string paren, priority;
		std::cin >> paren >> priority;

		std::stack< std::string::iterator > stack;
		for( std::string::iterator it = paren.begin(); it != paren.end(); ++it )
		{
			if( isOpenParen(*it) )
			{
				stack.push(it);
			}
			else
			{
				char open = *stack.top();
				char close = *it;
				if( getPairParen( open ) != close )
				{
					if( priority.find( open ) < priority.find( getPairParen(close) ) )
					{
						*it = getPairParen( open );
					}
					else
					{
						*stack.top() = getPairParen( close );
					}
				}

				stack.pop();
			}
		}

		std::cout << paren << std::endl;
	}

	return 0;
}