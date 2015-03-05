#include <iostream>
#include <queue>

int main( int argc, char** argv )
{
	int numTestCase;
	std::cin >> numTestCase;
	
	while( numTestCase-- )
	{
		int length;
		std::cin >> length;

		std::priority_queue<int, std::vector<int>, std::greater<int>> queue;
		for( int i = 0; i < length; ++i )
		{
			int n;
			std::cin >> n;
			queue.push(n);
		}

		int sum = 0;
		while( queue.size() > 1 )
		{
			int a = queue.top();
			queue.pop();
			int b = queue.top();
			queue.pop();
			sum += a+b;
			queue.push(a+b);
		}

		std::cout << sum << std::endl;
	}

	return 0;
}