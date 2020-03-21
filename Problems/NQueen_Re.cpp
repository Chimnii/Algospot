#include <stdio.h>
#include <vector>
#include <cmath>
struct point { int x, y; point( int _x, int _y ) : x(_x), y(_y) {} };

bool check_nqueen( int n, const std::vector<point>& queens )
{
	const point& last = queens.back(); // check only last queen
	for (const point& queen : queens)
	{
		if (&last == &queen) continue;
		if (last.x == queen.x || last.y == queen.y || std::abs(last.x - queen.x) == std::abs(last.y - queen.y))
			return false;
	}
	return true;
}

int find_nqueen( int n, std::vector<point>& queens )
{
	if (queens.size() == n)
		return 1;

	int sum = 0;
	int x = queens.size();
	for (int i = 0; i < n; ++i)
	{
		queens.emplace_back( x, i );
		if (check_nqueen( n, queens ))
			sum += find_nqueen( n, queens );
		queens.pop_back();
	}
	return sum;
}

int main()
{
#ifdef FILEINPUT
	FILE* fin;
	freopen_s(&fin, "input.txt", "r", stdin);
#endif
	int num_testcase;
	scanf("%d\n", &num_testcase);

	while(num_testcase--)
	{
		int n;
		scanf("%d\n", &n);

		std::vector<point> queens;
		int answer = find_nqueen( n, queens );
		printf("%d\n", answer );
	}

	return 0;
}
