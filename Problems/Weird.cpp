#include <iostream>
#include <vector>

bool isGreaterSum( const int number, const std::vector<int>& divisors, int index )
{
	int sum = 0;
	for( int i = index; i < static_cast<int>( divisors.size() ); ++i )
	{
		sum += divisors[i];
	}

	return sum > number;
}

bool isExistSubset( const int number, const std::vector<int>& divisors, int index )
{
	if( number == 0 )
		return true;
	if( number < 0 )
		return false;
	if( index >= static_cast<int>( divisors.size() ) )
		return false;
	if( !isGreaterSum( number, divisors, index ) )
		return false;

	return isExistSubset( number - divisors[index], divisors, index + 1 ) || isExistSubset( number, divisors, index + 1 );
}

void getDivisors( const int number, std::vector<int>& divisors )
{
	for( int i = number - 1; i >= 1; --i )
	{
		if( number % i == 0 )
			divisors.push_back(i);
	}
}

int main( int argc, char** argv )
{
	int testCase;
	std::cin >> testCase;

	while( testCase-- )
	{
		int number;
		std::cin >> number;

		std::vector<int> divisors;

		getDivisors( number, divisors );
		
		if( isGreaterSum( number, divisors, 0 ) && !isExistSubset( number, divisors, 0 ) )
			std::cout << "weird" << std::endl;
		else
			std::cout << "not weird" << std::endl;
	}

	return 0;
}