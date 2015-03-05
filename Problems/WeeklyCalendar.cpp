#include <iostream>
#include <string>

const int DayOfMonth[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
const std::string DayOfWeek[8] = { "", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

int getIndexOfWeek( const std::string& dow )
{
	for( int i = 1; i <= 7; ++i )
	{
		if( DayOfWeek[i] == dow )
			return i;
	}

	return -1;
}

int main( int argc, char** argv )
{
	int testCase;
	std::cin >> testCase;

	while( testCase-- )
	{
		int month, day;
		std::string dow;
		std::cin >> month >> day >> dow;

		day = day - getIndexOfWeek( dow ) + 1;
		for( int i = 1; i <= 7; ++i )
		{
			if( day <= 0 )
			{
				month = ( month + 10 ) % 12 + 1;
				day += DayOfMonth[month];
			}
			else if( day > DayOfMonth[month] )
			{
				day = day - DayOfMonth[month];
				month = month % 12 + 1;
			}

			std::cout << day << ( i != 7 ? " " : "" );
			day += 1;
		}
		std::cout << std::endl;
	}

	return 0;
}