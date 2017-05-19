#include <cstdio>
#include <string>
#include <vector>
#include <map>

using std::vector;
using std::string;
using std::map;

struct letter
{
	vector<string> in, out;
	vector<bool> in_visited, out_visited;
};

inline char first(const string& s) { return s[0]; }
inline char last(const string& s) { return s[s.size() - 1]; }

bool get_trail(map<char, letter>& letters, vector<string>& trails);
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
		int num_word;
		scanf("%d\n", &num_word);
		
		map<char, letter> letters;
		for (int i = 0; i < num_word; ++i)
		{
			char wordbuffer[11];
			scanf("%s", wordbuffer);
			string word(wordbuffer);

			letters[first(word)].out.emplace_back(word);
			letters[first(word)].out_visited.emplace_back(false);
			letters[last(word)].in.emplace_back(word);
			letters[last(word)].in_visited.emplace_back(false);
		}

		vector<string> trails;
		if (get_trail(letters, trails))
		{
			for (auto& w : trails)
			{
				printf("%s ", w.c_str());
			}
			printf("\n");
		}
		else
		{
			printf("IMPOSSIBLE\n");
		}
	}

	return 0;
}

bool get_start(map<char, letter>& letters, char& start)
{
	char s = 0, f = 0;
	for (auto& l : letters)
	{
		if (l.second.in.size() == l.second.out.size() + 1)
		{
			if (f != 0)
				return false;

			f = l.first;
		}
		else if(l.second.in.size() + 1 == l.second.out.size())
		{
			if (s != 0)
				return false;
			s = l.first;
		}
		else if(l.second.in.size() != l.second.out.size())
		{
			return false;
		}
	}

	if (s == 0 && f ==0)
	{
		start = letters.begin()->first;
		return true;
	}
	else if(s != 0 && f !=0)
	{
		start = s;
		return true;
	}

	return false;
}

void get_circuit(map<char, letter>& letters, vector<string>& trails, char start)
{
	auto& l = letters[start];

	vector<string> circuit;
	for (size_t i = 0; i < l.out.size(); ++i)
	{
		if (!l.out_visited[i])
		{
			l.out_visited[i] = true;

			vector<string> new_circuit;
			new_circuit.emplace_back(l.out[i]);
			get_circuit(letters, new_circuit, last(l.out[i]));

			circuit.insert(circuit.begin(), new_circuit.begin(), new_circuit.end());
		}
	}

	trails.insert(trails.end(), circuit.begin(), circuit.end());
}

bool get_trail(map<char, letter>& letters, vector<string>& trails)
{
	char start;
	if (!get_start(letters, start))
	{
		return false;
	}

	get_circuit(letters, trails, start);

	return true;
}
