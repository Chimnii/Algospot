#include <stdio.h>

namespace my
{
	struct istream {};
	istream cin;

	inline bool is_num(char c) { return (c >= '0' && c <= '9'); }
	inline bool is_negative(char c) { return c == '-'; }
	inline istream& operator>>(istream& in, int& out)
	{
		char c; out = 0; bool neg = false;
		while (c = getchar()) { if (is_negative(c)) { neg = true; break; } if (is_num(c)) { out += (c - '0'); break; } }
		while (c = getchar()) { if (!is_num(c)) break; out *= 10; out += (c - '0'); }
		if (neg) out *= -1;
		return in;
	}
}

int main(int argc, char** argv)
{
	int num_testcase;
	my::cin >> num_testcase;

	while (num_testcase--)
	{
		int score_cs, score_hp;
		my::cin >> score_cs >> score_hp;

		int hit;
		if (score_cs > score_hp) hit = 0;
		else hit = score_hp - score_cs + 4;

		printf("%d\n", hit);
	}

	return 0;
}
