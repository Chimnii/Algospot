#include <stdio.h>
#include <iostream>

int changedIndex[1000001];
int low, high;

bool search( int begin, int end )
{
	int current;
	while( end >= begin )
	{
		current = ( begin + end ) / 2;
		if( changedIndex[current] <= low )
		{
			begin = current + 1;
		}
		else if( changedIndex[current] > high )
		{
			end = current - 1;
		}
		else
		{
			return true;
		}
	}

	return false;
}

int main( int argc, char** argv )
{
	int length = 0;
	char before, current;
	for( int index = 0; ; ++index )
	{
		scanf( "%c", &current );
		if( current == '\n' )
		{
			break;
		}

		if( index != 0 && current != before )
		{
			changedIndex[length++] = index;
		}

		before = current;
	}

	int numTestCase;
	scanf( "%d", &numTestCase );

	while( numTestCase-- )
	{
		int l, h;
		scanf( "%d %d", &l, &h ), 
		low = std::min( l, h );
		high = std::max( l, h );

		// low 초과 high 이하에 changedIndex가 있는가.
		if( search( 0, length - 1 ) )
			printf("No\n");
		else
			printf("Yes\n");
	}


	return 0;
}