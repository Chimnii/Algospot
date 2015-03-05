#include <iostream>

const int TURN_CLOCK_TABLE[10][5] = { {0,1,2,-1,-1}, {3,7,9,11,-1}, {4,10,14,15,-1}, {0,4,5,6,7}, {6,7,8,10,12}, {0,2,14,15,-1}, {3,14,15,-1,-1}, {4,5,7,14,15}, {1,2,3,4,5}, {3,4,5,9,13} };

struct Clock
{
public:
	enum E_CLOCK
	{
		TWELVE = 1,
		THREE = 2,
		SIX = 3,
		NINE = 4
	};

	E_CLOCK time;

	Clock() : time(TWELVE) {} 

	void setTime( int n )
	{
		switch(n)
		{
		case 12: time = TWELVE; break;
		case 3: time = THREE; break;
		case 6: time = SIX; break;
		case 9: time = NINE; break;
		}
	}

	void next( int n = 1 )
	{
		for( int i = 0; i < n; ++i )
		{
			time = ( time == NINE ? TWELVE : E_CLOCK(time + 1) );
		}
	}
};

bool checkClocks( Clock clocks[16] )
{
	for( int i = 0; i < 16; ++i )
	{
		if( clocks[i].time != Clock::TWELVE )
			return false;
	}

	return true;
}

void turnClock( Clock clocks[16], int turnIndex )
{
	for( int i = 0; i < 5; ++i )
	{
		if( TURN_CLOCK_TABLE[turnIndex][i] == -1 )
			break;

		clocks[ TURN_CLOCK_TABLE[turnIndex][i] ].next();
	}
}

int calcMinTurn( Clock clocks[16], int turnIndex )
{
	if( turnIndex >= 10 )
		return -1;

	int min = -1;
	for( int i = 0; i < 4; ++i )
	{
		if( checkClocks( clocks ) )
			return i;

		int turn = calcMinTurn( clocks, turnIndex + 1 );
		if( turn != -1 && ( min == -1 || turn + i < min ) )
			min = turn + i;

		turnClock( clocks, turnIndex );
	}

	return min;
}

int main( int argc, char** argv )
{
	int testCase;
	std::cin >> testCase;

	while( testCase-- )
	{
		Clock clocks[16];
		for( int i = 0; i < 16; ++i )
		{
			int n;
			std::cin >> n;
			clocks[i].setTime(n);
		}

		std::cout << calcMinTurn( clocks, 0 ) << std::endl;
	}

	return 0;
}
