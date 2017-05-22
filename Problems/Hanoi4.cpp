#include <cstdio>
#include <cmath>
#include <vector>
#include <queue>
#include <algorithm>

using std::vector;
using std::queue;

constexpr int num_top = 4;
constexpr int max_disk = 12;

int get(int state, int index) { return (state >> (index * 2)) & 3; }
int set(int state, int index, int value) { return (state & ~(3 << (index * 2))) | (value << (index * 2)); }
int make(const vector<int>& values)
{
	int result = 0;
	for (auto rit = values.rbegin(); rit != values.rend(); ++rit)
	{
		result = (result << 2) + *rit;
	}
	return result;
}

int calc_minimum_moving(const int num_disk, const int begin, const int end);
int main()
{
#ifdef FILEINPUT
	FILE* fin;
	freopen_s(&fin, "input.txt", "r", stdin);
#endif
	
	int num_testcase;
	scanf("%d\n", &num_testcase);

	while (num_testcase--)
	{
		int num_disk;
		scanf("%d\n", &num_disk);
		
		vector<int> vec_begin(num_disk, -1), vec_end(num_disk, num_top - 1);
		for (int i = 0; i < num_top; ++i)
		{
			int n, d;
			scanf("%d", &n);

			while (n--)
			{
				scanf("%d", &d);
				vec_begin[d-1] = i;
			}
		}

		int begin = make(vec_begin), end = make(vec_end);
		int moving = calc_minimum_moving(num_disk, begin, end);
		printf("%d\n", moving);
	}

	return 0;
}

int sgn(int x) { if (!x) return 0; return x > 0 ? 1 : -1; }
int incr(int x) { if (x < 0) return x-1; return x+1; }

int states[1 << (max_disk * 2)];
int calc_minimum_moving(const int num_disk, const int begin, const int end)
{
	std::fill(states, states + sizeof(states) / sizeof(int), 0);

	if (begin == end)
		return 0;
	
	queue<int> q;
	q.emplace(begin);
	q.emplace(end);
	states[begin] = 1;
	states[end] = -1;
	while (!q.empty())
	{
		int current = q.front();
		q.pop();

		int top[4] = {-1, -1, -1, -1};
		for (int i = num_disk - 1; i >= 0; --i)
		{
			top[get(current, i)] = i;
		}

		for (int i = 0; i < 4; ++i)
		{
			if (top[i] == -1)
				continue;

			for (int j = 0; j < 4; ++j)
			{
				if (i == j || (top[j] != -1 && top[j] < top[i]) )
					continue;

				int next = set(current, top[i], j);
				if (states[next] == 0)
				{
					states[next] = incr(states[current]);
					q.emplace(next);
				}
				else if (sgn(states[next]) != sgn(states[current]))
				{
					return std::abs(states[next]) + std::abs(states[current]) - 1;
				}
			}
		}
	}
	
	return -1;
}
