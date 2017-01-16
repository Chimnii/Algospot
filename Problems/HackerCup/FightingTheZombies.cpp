#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

const double epsilon = std::numeric_limits<double>::epsilon();

struct point
{
	double x, y;
	bool operator <(const point& other) const
	{
		if (x < other.x) return true;
		else if(x == other.x) return y < other.y;
		else return false;
	}
};

int n, r;
point zombies[50];

int calc_maximum_death();
int main()
{
	int t;
	scanf_s("%d", &t);

	for (int i = 1; i <= t; ++i)
	{
		scanf_s("%d %d", &n, &r);

		for (int z = 0; z < n; ++z)
		{
			scanf_s("%lf %lf", &zombies[z].x, &zombies[z].y);
		}
		std::sort(&zombies[0], &zombies[n]);

		int maximum_death = calc_maximum_death();
		printf("Case #%d: %d\n", i, maximum_death);
	}

	return 0;
}

inline double dist2(const point& p1, const point& p2)
{
	return std::pow(p1.x-p2.x, 2) + std::pow(p1.y-p2.y, 2);
}

void divide_points(const point& p1, const point& p2, const point& p3, std::vector<int>& in, std::vector<int>& out)
{
	point c;
	double bx, cx, dx, by, cy, dy, r2;
	bx = p1.x; by = p1.y;
	cx = p2.x; cy = p2.y;
	dx = p3.x; dy = p3.y;

	double temp = cx*cx+cy*cy;
    double bc = (bx*bx + by*by - temp)/2.0;
    double cd = (temp - dx*dx - dy*dy)/2.0;
    double det = (bx-cx)*(cy-dy)-(cx-dx)*(by-cy);
	if (fabs(det) < epsilon)
	{
		c.x = (dx+bx)/2;
		c.y = (dy+by)/2;
		r2 = (c.x-bx)*(c.x-bx)+(c.y-by)*(c.y-by);
	}
	else
	{
		det = 1.0 / det;
		c.x = (bc*(cy-dy)-cd*(by-cy))*det;
		c.y = ((bx-cx)*cd-(cx-dx)*bc)*det;
		r2 = (c.x-bx)*(c.x-bx)+(c.y-by)*(c.y-by);
	}

	for (int i = 0; i < n; ++i)
	{
		double d2 = dist2(c, zombies[i]);
		if (d2 < r2 || fabs(d2-r2) < epsilon)
		{
			in.emplace_back(i);
		}
		else
		{
			out.emplace_back(i);
		}
	}
}

struct circle
{
	int p1, p2, p3;
	std::vector<int> in, out;

	circle(int _p1, int _p2, int _p3) : p1(_p1), p2(_p2), p3(_p3) {}
};

int square_max(const std::vector<int>& points)
{
	int max_count = 0;

	int count = points.size(), prev_j = 0;
	for (int i = 0; i < count; ++i)
	{
		for (int j = std::max(i+1,prev_j); j < count; ++j)
		{
			if (zombies[points[j]].x - zombies[points[i]].x > r)
			{
				break;
			}
			prev_j = j;
		}

		std::vector<double> ys;
		for (int yi = i; yi <= prev_j; ++yi)
		{
			ys.emplace_back(zombies[points[yi]].y);
		}
		std::sort(ys.begin(), ys.end());

		int ycount = ys.size(), prev_yj = 0;
		for (int yi = 0; yi < ycount; ++yi)
		{
			for (int yj = std::max(yi+1,prev_yj); yj < ycount; ++yj)
			{
				if (ys[yj] - ys[yi] > r)
				{
					break;
				}
				prev_yj = yj;
			}

			max_count = std::max(max_count, prev_yj-yi+1);
		}
	}

	return max_count;
}

int calc_maximum_death()
{
	std::vector<circle> circles;
	for (int i = 0; i < n; ++i)
	{
		for (int j = i+1; j < n; ++j)
		{
			for (int k = j+1; k < n; ++k)
			{
				/*
				assumption
				only case that 3 points are all in square, draw circle land get inner points.
				except inner points, draw square maximally, and plus circle points;
				*/
				
				if (std::max({zombies[i].x, zombies[j].x, zombies[k].x}) - std::min({zombies[i].x, zombies[j].x, zombies[k].x}) > r
					|| std::max({zombies[i].y, zombies[j].y, zombies[k].y}) - std::min({zombies[i].y, zombies[j].y, zombies[k].y}) > r)
				{
					continue;
				}

				circles.emplace_back(i, j, k);
			}

			circles.emplace_back(i, j, j);
		}
		circles.emplace_back(i, i, i);
	}

	int total_count = 0;
	for (auto& c : circles)
	{
		divide_points(zombies[c.p1], zombies[c.p2], zombies[c.p3], c.in, c.out);

		int inmax = square_max(c.in);
		int outmax = square_max(c.out);
		total_count = std::max(total_count, inmax + outmax);
	}

	return total_count;
}
