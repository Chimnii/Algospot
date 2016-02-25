#include <iostream>

const int LN = 1000000007;
int modpow( long long A, long long X )
{
	int acc = 1;
	while(X)
	{
		A %= LN;
		if(X%2)
			acc = (A*acc)%LN;
			
		A = A*A;
		X /= 2;
	}

	return acc;
}


int main()
{
	int M;
	while( std::cin >> M )
	{
		int N, S, acc = 0;
		for( int i = 0; i < M; ++i )
		{
			std::cin >> N >> S;
			int rev = modpow(N, LN-2);
			int ans = ((long long)S*rev)%LN;
			acc = (acc+ans)%LN;
		}
		std::cout << acc << std::endl;
	}

	return 0;
}
