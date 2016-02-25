#include <iostream>

const int LN = 1000000007;

int main()
{
	long long H, W;
	while( std::cin >> H >> W )
	{
		long long E = (((H+2)%LN)*((W+2)%LN))%LN;
		std::cout << E << std::endl;
	}
	return 0;
}
