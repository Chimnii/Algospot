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

const int size = 200004;
int kinds[size] = {0,};

int calc_kind(int n)
{
	if( kinds[n] > 0 )
		return kinds[n];
	
	int acc = calc_kind(n-2);
	for( int i = 2; i <= n; i+=2 )
	{
		if( (n-i)%4 == 0 )
		{
			acc += ((calc_kind(i)%LN) * (calc_kind((n-i)/2)%LN))%LN;
			acc %= LN;
		}
	}

	kinds[n] = acc;
	return acc;
}

int main()
{
	kinds[2] = 1;
	kinds[4] = 2;

	int N, K;
	while( std::cin >> N >> K )
	{
		long long acc = calc_kind(2*N);
		acc = acc * modpow(K,N);
		acc %= LN;
		std::cout << acc << std::endl;
	}

	return 0;
}