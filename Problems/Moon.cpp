#include <stdio.h>
#include <math.h>

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

double pi;

double get_area(double m, double s, double c)
{
	double t;
	double over_area = 0;

	t = 2 * acos((m*m + c*c - s*s) / (2 * m*c));
	over_area += m*m*(t - sin(t)) / 2;

	t = 2 * acos((s*s + c*c - m*m) / (2 * s*c));
	over_area += s*s*(t - sin(t)) / 2;

	return pi*m*m - over_area;
}

int main(int argc, char** argv)
{
	int num_testcase;
	my::cin >> num_testcase;

	pi = acos(-1.0);

	while (num_testcase--)
	{
		int r_moon, r_shadow, dist;
		my::cin >> r_moon >> r_shadow >> dist;

		printf("%.3f\n", get_area(r_moon, r_shadow, dist));
	}

	return 0;
}
