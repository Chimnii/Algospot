#include <iostream>

const int LN = 1000000007;
int main()
{
	long long A, X;
	while( std::cin >> A >> X )
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

		std::cout << acc << std::endl;
	}

	return 0;
}
