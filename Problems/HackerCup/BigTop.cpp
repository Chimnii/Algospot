#include <cstdio>
#include <map>

template <typename iterator, typename container>
bool is_first(iterator it, const container& c)
{
    return (it == c.begin());
}

template <typename iterator, typename container>
bool is_last(iterator it, const container& c)
{
    return (it != c.end()) && (next(it) == c.end());
}

std::map<double, double> heights;

double get_height(double x)
{
	auto emp = heights.emplace(x, 0);
	if (emp.second) // insert
	{
		auto it = emp.first;
		if (is_first(it, heights))
		{
			heights.erase(x);
			return 0;
		}
		if (is_last(it, heights))
		{
			heights.erase(x);
			return 0;
		}

		auto l = std::make_pair(prev(it)->first, prev(it)->second);
		auto r = std::make_pair(next(it)->first, next(it)->second);
		heights.erase(x);
		return (r.second > l.second ? (l.second + x - l.first) : (r.second + r.first - x));
	}
	else // already exist
	{
		return emp.first->second;
	}
}

double insert(double x, double  h)
{
	// printf("%d %d\n", x, h);

	double l = x - h;
	double m = x;
	double r = x + h;
	double lh, rh;

	std::map<double, double> modified;
	

	double old_h = get_height(m);
	if (old_h >= h)
	{
		return 0.0;
	}

	if (heights.find(m) != heights.end())
	{
		modified.emplace(m, heights[m]);
		heights[m] = h;
	}
	else
	{
		heights.emplace(m, h);
	}
	
	auto mit = heights.find(m);
	
	auto it = mit;
	while(true)
	{
		if (is_first(it, heights))
		{
			lh = 0.0;
			break;
		}

		it = prev(it);

		if (it->first <= l && it->second == 0)
		{
			lh = 0.0;
			break;
		}

		if (it->second <= (h - (m - it->first)))
		{
			modified.emplace(it->first, it->second);
		}
		else
		{
			l = (m - h + it->first + it->second) / 2;
			lh = get_height(l);
			break;
		}
	}
	heights.emplace(l, lh);

	it = mit;
	while(true)
	{
		if (is_last(it, heights))
		{
			rh = 0.0;
			break;
		}

		it = next(it);

		if (it->first >= r && it->second == 0)
		{
			rh = 0.0;
			break;
		}

		if (it->second <= (h - (it->first - m)))
		{
			modified.emplace(it->first, it->second);
		}
		else
		{
			r = (m + h + it->first - it->second) / 2;
			rh = get_height(r);
			break;
		}
	}
	heights.emplace(r, rh);


	double minus_area = 0.0;
	double px = l, ph = lh;
	for (auto it : modified)
	{
		heights.erase(it.first);
		minus_area += (it.first - px) * std::abs(it.second - ph) / 2;

		px = it.first;
		ph = it.second;
	}
	minus_area += (r - px) * std::abs(rh - ph) / 2;
	
	double plus_area = (lh + h) * (m - l) / 2 + (rh + h) * (r - m) / 2;

	heights.emplace(m, h);
	heights.emplace(l, lh);
	heights.emplace(r, rh);
	return plus_area - minus_area;
}

int main()
{
	FILE *fin, *fout;
	freopen_s(&fin, "HackerCup\\big_top_example_input.txt", "r", stdin);
	//freopen_s(&fout, "HackerCup\\Practice_out.txt", "w", stdout);

	int t;
	scanf_s("%d", &t);

	for (int i = 1; i <= t; ++i)
	{
		int n;
		scanf_s("%d\n", &n);

		int x1, ax, bx, cx;
		scanf_s("%d %d %d %d\n", &x1, &ax, &bx, &cx);

		int h1, ah, bh, ch;
		scanf_s("%d %d %d %d\n", &h1, &ah, &bh, &ch);

		heights.clear();

		double area = 0.0, total_area = 0.0;
		int x = x1, h = h1;
		while(n--)
		{
			area = area + insert(x, h);
			total_area += area;

			x = ((ax * x + bx) % cx) + 1;
			h = ((ah * h + bh) % ch) + 1;
		}

		printf("Case #%d: %f\n", i, total_area);
	}

	return 0;
}

