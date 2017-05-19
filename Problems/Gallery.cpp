#include <cstdio>
#include <vector>
#include <set>

using std::set;
using std::vector;

struct gallery
{
	set<int> halls;
	bool monitored = false;
	bool erased = false;
	bool is_leaf() { return halls.size() <= 1; }
};

int calc_min_camera(vector<gallery>& galleries);
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
		int num_gallery, num_hall;
		scanf("%d %d\n", &num_gallery, &num_hall);

		vector<gallery> galleries(num_gallery);
		for (int i = 0; i < num_hall; ++i)
		{
			int g1, g2;
			scanf("%d %d\n", &g1, &g2);
			galleries[g1].halls.emplace(g2);
			galleries[g2].halls.emplace(g1);
		}

		int min_camera = calc_min_camera(galleries);
		printf("%d\n", min_camera);
	}

	return 0;
}

void erase(vector<gallery>& galleries, int g)
{
	for (int n : galleries[g].halls)
	{
		galleries[n].halls.erase(g);
	}
	galleries[g].halls.clear();
	galleries[g].erased = true;
}

void monitor(vector<gallery>& galleries, int g)
{
	galleries[g].monitored = true;
	for (int n : galleries[g].halls)
	{
		galleries[n].monitored = true;
	}
}

int monitor_leaf(vector<gallery>& galleries, int g)
{
	int camera = 0;

	if (galleries[g].halls.size() == 0)
	{
		if (!galleries[g].monitored)
			++camera;
		erase(galleries, g);
	}
	else if(galleries[g].halls.size() == 1)
	{
		int p = *galleries[g].halls.begin();

		if (!galleries[g].monitored)
		{
			++camera;
			monitor(galleries, p);
		}
		erase(galleries, g);

		if (galleries[p].is_leaf())
		{
			camera += monitor_leaf(galleries, p);
		}
	}
	else
	{
		printf("error\n");
		camera = 0;
	}

	return camera;
}

int calc_min_camera(vector<gallery>& galleries)
{
	int camera = 0;

	int size = static_cast<int>(galleries.size());
	for (int g = 0; g < size; ++g)
	{
		if (galleries[g].erased)
			continue;

		if (galleries[g].is_leaf())
		{
			camera += monitor_leaf(galleries, g);
		}
	}
	
	return camera;
}
