#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>

using std::vector;
using std::set;

using range = std::pair<int, int>;
struct team
{
	range week, month;
};

enum class emeeting { none, week, month };

struct node
{
	int index;
	emeeting meeting;
	set<node*> in, out;

	bool is_leaf() { return in.size() == 0; }
};

class graph
{
public:
	graph(int num_team) : week(num_team), month(num_team)
	{
		for (int i = 0; i < num_team; ++i)
		{
			week[i].index = i;
			week[i].meeting = emeeting::week;
			month[i].index = i;
			month[i].meeting = emeeting::month;
		}
	}
	int size() { return static_cast<int>(week.size()); }
	node* get_node(int index, emeeting meeting)
	{
		return meeting == emeeting::week ? &week[index] : &month[index];
	}
	node* get_opposite(const node* n)
	{
		if (n->meeting == emeeting::week) return &month[n->index];
		else return &week[n->index];
	}
	void make_direction(node* i, node* j)
	{
		i->out.emplace(j);
		j->in.emplace(i);
	}
	void erase(node* n)
	{
		for (node* other : n->in)
		{
			other->out.erase(n);
		}
		for (node* other : n->out)
		{
			other->in.erase(n);
		}
		n->in.clear();
		n->out.clear();
	}

private:
	vector<node> week, month;
};

bool make_graph(vector<team>& teams, graph& nodes);
bool find_trivial(graph& nodes, vector<emeeting>& assigned);
bool find_leaf(graph& nodes, vector<emeeting>& assigned);
bool find_assignment(graph& nodes, vector<emeeting>& assigned);
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
		int num_team;
		scanf("%d\n", &num_team);

		vector<team> teams(num_team);
		for (int i = 0; i < num_team; ++i)
		{
			scanf("%d %d %d %d", &teams[i].week.first, &teams[i].week.second, &teams[i].month.first, &teams[i].month.second);
		}

		graph nodes(num_team);
		vector<emeeting> assigned(num_team, emeeting::none);
		if (!make_graph(teams, nodes))
		{
			printf("IMPOSSIBLE\n");
		}
		else if (!find_trivial(nodes, assigned))
		{
			printf("IMPOSSIBLE\n");
		}
		else if (!find_leaf(nodes, assigned))
		{
			printf("IMPOSSIBLE\n");
		}
		else if (!find_assignment(nodes, assigned))
		{
			printf("IMPOSSIBLE\n");
		}
		else
		{
			printf("POSSIBLE\n");
			for (int i = 0; i < num_team; ++i)
			{
				range t = assigned[i] == emeeting::week? teams[i].week : teams[i].month;
				printf("%d %d\n", t.first, t.second);
			}
		}
	}
	
	return 0;
}

bool is_conflict(const range& t1, const range& t2)
{
	return t1.second > t2.first && t1.first < t2.second;
}

bool make_graph(vector<team>& teams, graph& nodes)
{
	int size = static_cast<int>(teams.size());
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			if (i == j)
				continue;

			node* iw = nodes.get_node(i, emeeting::week);
			node* im = nodes.get_node(i, emeeting::month);
			node* jw = nodes.get_node(j, emeeting::week);
			node* jm = nodes.get_node(j, emeeting::month);
			if (is_conflict(teams[i].week, teams[j].week)) nodes.make_direction(iw, jm);
			if (is_conflict(teams[i].week, teams[j].month)) nodes.make_direction(iw, jw);
			if (is_conflict(teams[i].month, teams[j].week)) nodes.make_direction(im, jm);
			if (is_conflict(teams[i].month, teams[j].month)) nodes.make_direction(im, jw);
		}
	}

	return true;
}

bool try_assign(graph& nodes, vector<emeeting>& assigned, node* n)
{
	if (assigned[n->index] == emeeting::none)
	{
		assigned[n->index] = n->meeting;

		for (auto o : n->out)
		{
			if (!try_assign(nodes, assigned, o))
				return false;
		}
	}
	else
	{
		return (n->meeting == assigned[n->index]);
	}

	return true;
}

void do_assign(graph& nodes, vector<emeeting>& assigned, node* n)
{
	if (assigned[n->index] == emeeting::none)
	{
		assigned[n->index] = n->meeting;
		for (auto o : n->out)
		{
			do_assign(nodes, assigned, o);
		}
	}
}

bool assign(graph& nodes, vector<emeeting>& assigned, node* n)
{
	vector<emeeting> try_assigned(assigned);
	if (try_assign(nodes, try_assigned, n))
	{
		do_assign(nodes, assigned, n);
		return true;
	}

	return false;
}

bool check_unassignable(node* n)
{
	for (auto o1 : n->out)
	{
		for (auto o2 : n->out)
		{
			if (o1->index == o2->index && o1->meeting != o2->meeting)
				return true;
		}
	}

	return false;
}

bool find_trivial(graph& nodes, vector<emeeting>& assigned)
{
	for (int i = 0; i < nodes.size(); ++i)
	{
		node* w = nodes.get_node(i, emeeting::week);
		node* m = nodes.get_node(i, emeeting::month);
		
		if (check_unassignable(w))
		{
			if (!assign(nodes, assigned, m))
				return false;
		}
		if (check_unassignable(m))
		{
			if (!assign(nodes, assigned, w))
				return false;
		}
	}

	return true;
}

bool find_leaf(graph& nodes, vector<emeeting>& assigned)
{
	set<node*> leaves;
	for (int i = 0; i < nodes.size(); ++i)
	{
		node* n;
		n = nodes.get_node(i, emeeting::week);
		if (n->is_leaf())
			leaves.emplace(n);
		n = nodes.get_node(i, emeeting::month);
		if (n->is_leaf())
			leaves.emplace(n);
	}

	while (leaves.size() > 0)
	{
		node* n = *leaves.begin();
		leaves.erase(leaves.begin());

		if (assigned[n->index] == emeeting::none)
		{
			assign(nodes, assigned, nodes.get_opposite(n));
		}

		auto out(n->out);
		nodes.erase(n);

		for (auto o : out)
		{
			if (o->is_leaf())
				leaves.emplace(o);
		}
	}

	return true;
}

bool find_assignment(graph& nodes, vector<emeeting>& assigned)
{
	for (int i = 0; i < nodes.size(); ++i)
	{
		if (assigned[i] != emeeting::none)
			continue;

		for (int j = 0; j < 2; ++j)
		{
			vector<emeeting> try_assigned(assigned);
			if (assign(nodes, try_assigned, nodes.get_node(i, j == 0 ? emeeting::week : emeeting::month)))
			{
				if (find_assignment(nodes, try_assigned))
				{
					assigned.swap(try_assigned);
					return true;
				}
			}
		}

		return false;
	}

	return true;
}
