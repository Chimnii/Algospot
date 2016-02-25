#include <iostream>

const int LARGE_NUMBER = 1000000007;

template<int LN>
struct fraction
{
	int mod;
	fraction() : mod(0) {}
	fraction(int _denom, int _num)
	{
		mod = getmod(_denom, _num);
	}

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

	int getmod( int denom, int num )
	{
		int rev = modpow(denom, LN-2);
		int mod = ((long long)num*rev)%LN;
		return mod;
	}

	fraction operator+( const fraction& op )
	{
		return fraction((this->mod+op.mod)%LN);
	}
	fraction operator-( const fraction& op )
	{
		return fraction((this->mod-op.mod+LN)%LN);
	}
	fraction operator*( const fraction& op )
	{
		return fraction(((long long)(this->mod)*op.mod)%LN);
	}
	fraction operator/( const fraction& op )
	{
		return fraction(op.mod, this->mod);
	}

private:
	fraction(int _mod) : mod(_mod) {}
};
typedef fraction<LARGE_NUMBER> frac;

// Pn = A*Pn-1 + B*Pn+1
// A = Q/P, B = (P-Q)/P
int main()
{
	frac coef[101], prob[101];
	coef[0] = frac(1,0);
	prob[0] = frac(1,0);

	int P, Q, N, K;
	while( std::cin >> P >> Q >> N >> K )
	{
		prob[N] = frac(1,1);
		frac A(P,Q), B(P,P-Q);

		// Pn = coef[n] * Pn+1
		// Pn = A*Pn-1 + B*Pn+1
		// Pn = A*coef[n-1]*Pn + B*Pn+1
		// (1-A*coef[n-1])Pn = B*Pn+1
		// Pn = B/(1-A*coef[n-1])*Pn+1
		for( int i = 1; i < N; ++i )
		{
			coef[i] = B / (frac(1,1)-A*coef[i-1]);
		}

		int i = N;
		while(i != K)
		{
			--i;
			prob[i] = coef[i]*prob[i+1];
		}
		std::cout << prob[i].mod << std::endl;
	}

	return 0;
}


