#include <iostream>
const int LARGE_NUMBER = 1000000007;
const int size = 3001;

int fracs[size][size] = {0,};
template<int LN>
struct fraction
{
	int mod;
	fraction() : mod(0) {}
	fraction(int _denom, int _num)
	{
		if( _denom < size && _num < size && fracs[_denom][_num] )
		{
			mod = fracs[_denom][_num];
		}
		else
		{
			mod = getmod(_denom,_num);
			if( _denom < size && _num < size )
				fracs[_denom][_num] = mod;
		}
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


int N, L;
frac probs[size][size];

frac calc_prob( int remain_D, int remain_L )
{
	if( probs[remain_D][remain_L].mod != -1 )
		return probs[remain_D][remain_L];
	if( remain_D > remain_L )
		return frac();
	
	frac p1 = calc_prob(remain_D, remain_L-1) * frac(N, N-remain_D);
	frac p2 = calc_prob(remain_D-1, remain_L-1) * frac(N, remain_D);
	probs[remain_D][remain_L] = p1+p2;
	return probs[remain_D][remain_L];
}

int main()
{
	probs[0][0].mod = 1;
	for( int i = 1; i < size; ++i )
	{
		probs[i][0].mod = 0;
		probs[0][i].mod = 1;
	}

	while( std::cin >> N >> L )
	{
		int remain_D = 0, kind_D = 0;
		for( int i = 0; i < N; ++i )
		{
			int D;
			std::cin >> D;
			
			remain_D += D;
			if( D > 1 )
				kind_D += D-1;
		}

		N += kind_D;
		for( int i = 1; i <= N; ++i ) for( int j = 1; j <= L; ++j ) probs[i][j].mod = -1;

		frac prob = calc_prob( remain_D, L );
		std::cout << prob.mod << std::endl;
	}

	return 0;
}
