#include <iostream>

int numStudent;
bool friends[10][10];

int FindCombi( bool students[10], int num )
{
	if( num == 0 )
		return 1;

	int countCombi = 0;
	for( int s_i = 0; s_i < numStudent; ++s_i )
	{
		if( students[s_i] == false )
		{
			for( int f_i = s_i + 1; f_i < numStudent; ++f_i )
			{
				if( students[f_i] == false && friends[s_i][f_i] == true )
				{
					students[s_i] = true;
					students[f_i] = true;
					countCombi += FindCombi( students, num - 2 );
					students[s_i] = false;
					students[f_i] = false;
				}
			}

			break;
		}
	}

	return countCombi;
}

int main( int argc, char** argv )
{
	int numTestCase;
	std::cin >> numTestCase;

	while( numTestCase-- )
	{
		int numFriend;
		std::cin >> numStudent >> numFriend;

		for( int i = 0; i < numStudent; ++i )
			for( int j = 0; j < numStudent; ++j )
				friends[i][j] = false;

		for( int i = 0; i < numFriend; ++i )
		{
			int f1, f2;
			std::cin >> f1 >> f2;
			friends[f1][f2] = true;
			friends[f2][f1] = true;
		}

		bool students[10] = {false,};
		std::cout << FindCombi( students, numStudent ) << std::endl;
	}

	return 0;
}