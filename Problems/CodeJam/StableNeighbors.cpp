#include <cstdio>
#include <cmath>
#include <unordered_set>
#include <string>

const int kind = 6;
const int maxstall = 1001;
enum ehorse
{
	R = 0,
	O = 1,
	Y = 2,
	G = 3,
	B = 4,
	V = 5
};
char tochar[kind] = {'R', 'O', 'Y', 'G', 'B', 'V'};

int n;
int horses[kind];
int answer[maxstall];

struct colorset
{
public:
	colorset(int _horses[kind])
	{
		for (int i = 0; i < kind; ++i)
			horses[i] = _horses[i];
	}
	bool operator ==(const colorset& other) const
	{
		for (int i = 0; i < kind; ++i)
		{
			if (horses[i] != other.horses[i])
				return false;
		}
		return true;
	}

	int horses[kind];
};

namespace std
{
	template<>
	struct hash<colorset>
	{
		inline size_t operator()(const colorset& x) const
		{
			std::string str;
			for (int i = 0 ; i < kind; ++i)
			{
				int n = 1000;
				n += x.horses[i];
				str += std::to_string(n);
			}

			return std::hash<std::string>{}(str);
		}
	};
}

std::unordered_set<colorset> memo[maxstall][kind];
bool is_neighborable(int l, int r)
{
	switch(l)
	{
	case R: return (r == Y || r == G || r == B);
	case O: return (r == B);
	case Y: return (r == R || r == B || r == V);
	case G: return (r == R);
	case B: return (r == R || r == O || r == Y);
	case V: return (r == Y);
	default: return false;
	}
}

bool is_memoized(int index, int horse)
{
	colorset c(horses);
	return (memo[index][horse].find(c) != memo[index][horse].end());
}

void memoize(int index, int horse)
{
	colorset c(horses);
	memo[index][horse].emplace(c);
}

bool backtracking(int index)
{
	if (index == n)
	{
		return is_neighborable(answer[index-1], answer[0]);
	}

	int before = answer[index-1];
	if (is_memoized(index-1, before))
	{
		return false;
	}

	for (int h = 0; h < kind; ++h)
	{
		if (is_neighborable(before, h) && horses[h] != 0)
		{
			answer[index] = h;
			horses[h]--;

			bool result = backtracking(index+1);
			if (result)
			{
				return true;
			}
			else
			{
				memoize(index, h);
			}

			answer[index] = -1;
			horses[h]++;
		}
	}

	return false;
}

int main()
{
	FILE *fin, *fout;
	freopen_s(&fin, "CodeJam\\StableNeighbors_in.txt", "r", stdin);
	//freopen_s(&fout, "CodeJam\\StableNeighbors_out.txt", "w", stdout);

	int t;
	scanf_s("%d", &t);

	for (int i = 1; i <= t; ++i)
	{
		scanf_s("%d", &n);

		for (int j = 0; j < kind; ++j)
		{
			for (int k = 0; k < n; ++k)
			{
				memo[k][j].clear();
			}
		}

		for (int j = 0; j < kind; ++j)
		{
			scanf_s("%d", &horses[j]);
		}

		for (int j = 0; j < kind; ++j)
		{
			if (horses[j] != 0)
			{
				answer[0] = j;
				horses[j]--;
				break;
			}
		}

		printf("Case #%d: ", i);
		bool result = backtracking(1);
		if (result)
		{
			for (int j = 0; j < n; ++j)
			{
				printf("%c", tochar[answer[j]]);
			}
		}
		else
		{
			printf("IMPOSSIBLE");
		}
		printf("\n");
	}

	return 0;
}
