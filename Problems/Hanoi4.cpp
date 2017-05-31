#include <cmath>
#include <iostream>
#include <chrono>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>

#ifdef FILEINPUT
#define TEST
#endif

constexpr int num_top = 4;
constexpr int max_disk = 12;

namespace hanoi
{
	int num_disk;
	int states[1 << (max_disk * 2)];
	int priority[1 << (max_disk * 2)];
	size_t searched_count;
	size_t visited_count;
	int get(int state, int index) { return (state >> ((num_disk-index-1) * 2)) & 3; }
	int set(int state, int index, int value) { return (state & ~(3 << ((num_disk-index-1) * 2))) | (value << ((num_disk-index-1) * 2)); }
	int make(const std::vector<int>& values)
	{
		int result = 0;
		for (auto it = values.begin(); it != values.end(); ++it)
		{
			result = (result << 2) + *it;
		}
		return result;
	}
	int get_priority(int state)
	{	
		bool bcompleted = true;
		int completed = 0;
		int tower[num_top] = {0,};

		for (int i = 0; i < num_disk; ++i)
		{
			int n = state & 3;
			if (bcompleted && n == 3)
			{
				completed++;
			}
			else
			{
				bcompleted = false;
				tower[n]++;
			}
			state = state >> 2;
		}

		int result = 0;
		for (int i = 0; i < num_top - 1; ++i)
		{
			result += tower[i];
			//result += (tower[i] - 1) * (tower[i] - 2) / 2;
		}
		result += (tower[num_top-1] - completed) * 2;
		//result += (tower[num_top-1] - completed - 1) * (tower[num_top-1] - completed - 2) / 2;
		return result;
	}
};

template<typename timetype = std::chrono::milliseconds>
struct measure
{
	template<typename F, typename ...Args>
	static auto duration(F&& func, Args&&... args)
	{
		auto begin = std::chrono::steady_clock::now();
		auto result = std::forward<decltype(func)>(func)(std::forward<Args>(args)...);
		auto end = std::chrono::steady_clock::now();
		return std::make_pair(result, std::chrono::duration_cast<timetype>(end - begin).count());
	}
};

void print(const char* method, const int result, const long long duration)
{
#ifdef TEST
	std::cout << result << " (" << method << ", " << duration << " ms, " << hanoi::visited_count << ", " << hanoi::searched_count << ")\n";
#else
	std::cout << result << "\n";
#endif
}

int bfs(const int begin, const int end);
int bidir(const int begin, const int end);
int bfs_with_priorityqueue(const int begin, const int end);
int a_star(const int begin, const int end);
int main()
{
#ifdef FILEINPUT
	FILE* fin;
	freopen_s(&fin, "input.txt", "r", stdin);
#endif
	std::ios::sync_with_stdio(false);

	int num_testcase;
	std::cin >> num_testcase;

	while (num_testcase--)
	{
		std::cin >> hanoi::num_disk;
		
		std::vector<int> vec_begin(hanoi::num_disk, -1), vec_end(hanoi::num_disk, num_top - 1);
		for (int i = 0; i < num_top; ++i)
		{
			int n, d;
			std::cin >> n;

			while (n--)
			{
				std::cin >> d;
				vec_begin[d-1] = i;
			}
		}
		int begin = hanoi::make(vec_begin), end = hanoi::make(vec_end);

		// bidir
		auto result = measure<>::duration(bidir, begin, end);
		print("bidir", result.first, result.second);

#ifdef TEST
		// bfs
		result = measure<>::duration(bfs, begin, end);
		print("bfs", result.first, result.second);

		// bidir with priority queue
		result = measure<>::duration(bfs_with_priorityqueue, begin, end);
		print("bfs with priority queue", result.first, result.second);

		// a*
		result = measure<>::duration(a_star, begin, end);
		print("a*", result.first, result.second);
#endif
	}

	return 0;
}

inline void get_topdisk(int top[num_top], int state)
{
	for (int i = 0; i < num_top; ++i)
	{
		top[i] = -1;
	}

	for (int i = hanoi::num_disk - 1; i >= 0; --i)
	{
		top[hanoi::get(state, i)] = i;
	}
}

int bfs(const int begin, const int end)
{
	std::fill(hanoi::states, hanoi::states + sizeof(hanoi::states) / sizeof(int), -1);

	if (begin == end)
		return 0;

	std::queue<int> queue;
	queue.emplace(begin);
	hanoi::states[begin] = 0;

	hanoi::visited_count = 0;
	hanoi::searched_count = 0;
	while (!queue.empty())
	{
		++hanoi::visited_count;

		int current = queue.front();
		queue.pop();

		int top[num_top];
		get_topdisk(top, current);

		for (int i = 0; i < num_top; ++i)
		{
			if (top[i] == -1)
				continue;

			for (int j = 0; j < num_top; ++j)
			{
				if (i == j || (top[j] != -1 && top[j] < top[i]) )
					continue;

				int next = hanoi::set(current, top[i], j);
				if (hanoi::states[next] == -1)
				{
					++hanoi::searched_count;
					hanoi::states[next] = hanoi::states[current] + 1;
					queue.emplace(next);
				}
				
				if (next == end)
				{
					return hanoi::states[next];
				}
			}
		}
	}

	return hanoi::states[end];
}

int sgn(int x) { if (!x) return 0; return x > 0 ? 1 : -1; }
int incr(int x) { if (x < 0) return x-1; return x+1; }

int bidir(const int begin, const int end)
{
	std::fill(hanoi::states, hanoi::states + sizeof(hanoi::states) / sizeof(int), 0);

	if (begin == end)
		return 0;
	
	std::queue<int> queue;
	queue.emplace(begin);
	queue.emplace(end);
	hanoi::states[begin] = 1;
	hanoi::states[end] = -1;

	hanoi::visited_count = 0;
	hanoi::searched_count = 0;
	while (!queue.empty())
	{
		++hanoi::visited_count;

		int current = queue.front();
		queue.pop();

		int top[num_top];
		get_topdisk(top, current);

		for (int i = 0; i < 4; ++i)
		{
			if (top[i] == -1)
				continue;

			for (int j = 0; j < 4; ++j)
			{
				if (i == j || (top[j] != -1 && top[j] < top[i]) )
					continue;

				int next = hanoi::set(current, top[i], j);
				if (hanoi::states[next] == 0)
				{
					++hanoi::searched_count;
					hanoi::states[next] = incr(hanoi::states[current]);
					queue.emplace(next);
				}
				else if (sgn(hanoi::states[next]) != sgn(hanoi::states[current]))
				{
					return std::abs(hanoi::states[next]) + std::abs(hanoi::states[current]) - 1;
				}
			}
		}
	}
	
	return hanoi::states[end];
}

int bfs_with_priorityqueue(const int begin, const int end)
{
	std::fill(hanoi::states, hanoi::states + sizeof(hanoi::states) / sizeof(int), -1);

	if (begin == end)
		return 0;

	int queueindex = 0;
	std::priority_queue<std::pair<int, int>> queue;
	queue.emplace(queueindex--, begin);
	hanoi::states[begin] = 0;

	hanoi::visited_count = 0;
	hanoi::searched_count = 0;
	while (!queue.empty())
	{
		++hanoi::visited_count;

		int current = queue.top().second;
		queue.pop();

		int top[num_top];
		get_topdisk(top, current);

		for (int i = 0; i < num_top; ++i)
		{
			if (top[i] == -1)
				continue;

			for (int j = 0; j < num_top; ++j)
			{
				if (i == j || (top[j] != -1 && top[j] < top[i]) )
					continue;

				int next = hanoi::set(current, top[i], j);
				if (hanoi::states[next] == -1)
				{
					++hanoi::searched_count;
					hanoi::states[next] = hanoi::states[current] + 1;
					queue.emplace(queueindex--, next);
				}
				
				if (next == end)
				{
					return hanoi::states[next];
				}
			}
		}
	}

	return hanoi::states[end];
}

int a_star(const int begin, const int end)
{
	std::fill(hanoi::states, hanoi::states + sizeof(hanoi::states) / sizeof(int), -1);

	if (begin == end)
		return 0;

	std::priority_queue<std::pair<int, int>> queue;
	queue.emplace(-hanoi::get_priority(begin), begin);
	hanoi::states[begin] = 0;

	hanoi::visited_count = 0;
	hanoi::searched_count = 0;
	while (!queue.empty())
	{
		++hanoi::visited_count;

		int value = queue.top().first;
		int current = queue.top().second;
		queue.pop();

		if (hanoi::states[end] != -1 && value >= hanoi::states[end])
		{
			return hanoi::states[end];
		}

		int top[num_top];
		get_topdisk(top, current);

		for (int i = 0; i < num_top; ++i)
		{
			if (top[i] == -1)
				continue;

			for (int j = 0; j < num_top; ++j)
			{
				if (i == j || (top[j] != -1 && top[j] < top[i]) )
					continue;

				int next = hanoi::set(current, top[i], j);
				if (hanoi::states[next] == -1 || hanoi::states[next] > hanoi::states[current] + 1)
				{
					++hanoi::searched_count;
					hanoi::states[next] = hanoi::states[current] + 1;
					queue.emplace(-hanoi::states[next] - hanoi::get_priority(hanoi::states[next]), next);
				}
			}
		}
	}

	return hanoi::states[end];
}
