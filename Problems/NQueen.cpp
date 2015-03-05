#include <iostream>
#define BY_RECURSIVE 1
#define BY_LOOP 0 // fail

bool queenCheck( bool board[12][12], int size, int row, int col )
{
	for( int k = 1; k < size; ++k )
	{
		if( row - k >= 0 && board[row-k][col] == true )
			return false;
		if( row + k < size && board[row+k][col] == true )
			return false;
		if( col - k >= 0 && board[row][col-k] == true )
			return false;
		if( col + k < size && board[row][col+k] == true )
			return false;
		if( row - k >= 0 && col - k >= 0 && board[row-k][col-k] == true )
			return false;
		if( row + k < size && col + k < size && board[row+k][col+k] == true )
			return false;
		if( row - k >= 0 && col + k < size && board[row-k][col+k] == true )
			return false;
		if( row + k < size && col - k >= 0 && board[row+k][col-k] == true )
			return false;
	}

	return true;
}

#if BY_RECURSIVE
int nQueen( bool board[12][12], int size, int row, int col, int n )
{
	if( n >= size )
		return 1;
	if( row >= size )
		return 0;
	if( col >= size )
		return 0;

	int set = 0, noSet = 0;
	
	board[row][col] = true;
	if( queenCheck( board, size, row, col ) )
		set = nQueen( board, size, row+1, 0, n+1 );

	board[row][col] = false;
	noSet = nQueen( board, size, row, col+1, n );

	return set + noSet;
}
#endif

#if BY_LOOP
#include <stack>

struct State
{
	int row, col, phase;
	enum STATE
	{
		NOSET,
		SET,
		UNSET,
	};
	State( int _row, int _col, int _phase ) : row(_row), col(_col), phase(_phase) {}
};

int nQueen( bool board[12][12], int size )
{
	int answer = 0;

	std::stack<State> stack;
	stack.push( State( 0, 0, 0 ) );
	while(true)
	{
		State state = stack.top();

		if( state.phase == State::NOSET )
		{
			stack.pop();
			if( queenCheck( board, size, state.row, state.col ) )
			{
				stack.push( State( state.row, state.col, State::SET ) );
			}
			else
			{
				stack.push( State( state.row, state.col, State::UNSET ) );
			}
			continue;
		}
		else if( state.phase == State::SET )
		{	
			board[state.row][state.col] = true;
			if( state.row == size - 1 )
			{	
				++answer;
				stack.pop();
				stack.push( State( state.row, state.col, State::UNSET ) );
			}
			else
			{
				stack.push( State( state.row + 1, 0, State::NOSET ) );
			}
		}
		else if( state.phase == State::UNSET )
		{
			board[state.row][state.col] = false;

			stack.pop();
			if( state.col < size - 1 )
			{
				stack.push( State( state.row, state.col + 1, State::NOSET ) );
			}
			else if( stack.size() > 0 )
			{
				state = stack.top();
				stack.pop();
				stack.push( State( state.row, state.col, State::UNSET ) );
			}
			else
			{
				break;
			}
		}
	}

	return answer;
}
#endif

int main( int argc, char** argv )
{
	int testCase;
	std::cin >> testCase;

	while( testCase-- )
	{
		int size;
		std::cin >> size;

		bool board[12][12] = {0,};

#if BY_RECURSIVE
		std::cout << nQueen( board, size, 0, 0, 0 ) << std::endl;
#elif BY_LOOP
		std::cout << nQueen( board, size ) << std::endl;
#endif
	}

	return 0;
}