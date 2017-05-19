#include <cstdio>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

using std::vector;
using std::pair;
using std::string;
using std::queue;

struct node
{
	int self = -1;
	int num = 0;
	bool searched = false, visited = false;
	pair<node*, int> parent = {nullptr, -1};
	vector<pair<int, int>> out;
};
using graph = vector<vector<node>>;

void split_digits(vector<int>& usable_digits, const string& digits);
void make_graph(graph& nodes, const vector<int>& usable_digits, const int n, const int m);
bool calc_shortest_path(graph& nodes, const int n, const int m, vector<int>& shortest_path);
int main()
{
#ifdef FILEINPUT
	FILE *fin;
	freopen_s(&fin, "input.txt", "r", stdin);
#endif

	int num_testcase;
	scanf("%d\n", &num_testcase);
	
	while (num_testcase--)
	{
		int n, m;
		char sz_digits[16];
		scanf("%s %d %d", sz_digits, &n, &m);

		vector<int> usable_digits;
		split_digits(usable_digits, sz_digits);

		graph nodes(2, vector<node>(n));
		make_graph(nodes, usable_digits, n, m);
		
		vector<int> shortest_path;
		if (calc_shortest_path(nodes, n, m, shortest_path))
		{
			for (int d : shortest_path)
				printf("%d", d);
			printf("\n");
		}
		else
		{
			printf("IMPOSSIBLE\n");
		}
	}

	return 0;
}

void split_digits(vector<int>& usable_digits, const string& digits)
{
	for (char d : digits)
	{
		usable_digits.emplace_back(d-'0');
	}

	std::sort(usable_digits.begin(), usable_digits.end());
}

void make_graph(graph& nodes, const vector<int>& usable_digits, const int n, const int m)
{
	for (int node_i = 0; node_i < n; ++node_i)
	{
		for (int digit : usable_digits)
		{
			int next = (node_i * 10 + digit) % n;
			for (int j = 0; j < 2; ++j)
			{
				nodes[j][node_i].self = node_i;
				nodes[j][node_i].out.emplace_back(digit, next);
			}
		}
	}
}

bool is_acceptable(const int target, const int current)
{
	return (current == -1 || current >= target);
}

bool calc_shortest_path(graph& nodes, const int n, const int m, vector<int>& shortest_path)
{
	node head(nodes[0][0]);

	queue<node*> queue;
	queue.emplace(&head);

	bool result = false;
	while (queue.size() > 0)
	{
		node* current = queue.front();
		queue.pop();
		
		if (current->visited)
		{
			continue;
		}
		current->visited = true;


		if (current->self == m && is_acceptable(n, current->num))
		{
			result = true;
			break;
		}

		for (auto o : current->out)
		{
			int next_num = is_acceptable(n, current->num) ? -1 : current->num * 10 + o.first;
			int sl = is_acceptable(n, next_num) ? 1 : 0;

			node& next = nodes[sl][o.second];
			if (next.searched)
				continue;

			next.parent = std::make_pair(current, o.first);
			next.num = next_num;
			next.searched = true;
			queue.emplace(&next);
		}
	}

	if (result)
	{
		node* p = &nodes[1][m];
		while (p->parent.first)
		{
			shortest_path.emplace_back(p->parent.second);
			p = p->parent.first;
		}
		std::reverse(shortest_path.begin(), shortest_path.end());
	}

	return result;
}
