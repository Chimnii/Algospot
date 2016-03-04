#include <iostream>
#include <set>

int main( int argc, char** argv )
{
	int N, M;
	while( std::cin >> N >> M )
	{
		int remain = N;
		std::set<int> set;
		set.insert(3);
		set.insert(5);
		set.insert(2);
		set.insert(8);
		auto it = set.begin();
		auto it2 = it; it2++;
		auto it3 = it2; it3++;
		auto it4 = it3; it4++;
		std::cout << std::endl;
	}

	return 0;
}
