#include <stdio.h>
#include <vector>
#include <queue>
#include <functional>

namespace my
{
	struct istream{};
	istream cin;

	inline bool is_num( char c ){ return ( c >= '0' && c <= '9' ); }
	inline bool is_negative( char c ){ return c == '-'; }
	inline istream& operator>>( istream& in, int& out )
	{
		char c; out = 0; bool neg = false;
		while( c = getchar() ){ if( is_negative(c) ){ neg = true; break; } if( is_num(c) ){ out += (c-'0'); break; } }
		while( c = getchar() ){ if( !is_num(c) ) break; out *= 10; out += (c-'0'); }
		if( neg ) out *= -1;
		return in;
	}
}


namespace dijkstra
{
	class iedge
	{
	public:
		virtual int dist() const = 0;
		virtual int dest() const = 0;
	};

	class ivertex
	{
		class range_edges
		{
		public:
			explicit range_edges(const ivertex& _v) : v(_v) {}
			friend auto begin(const range_edges& er) { return er.v.begin(); }
			friend auto end(const range_edges& er) { return er.v.end(); }
			
		private:
			const ivertex& v;
		};

	public:
		virtual const std::vector<iedge>::iterator begin() const = 0;
		virtual const std::vector<iedge>::iterator end() const = 0;
		virtual const range_edges edges() const { return range_edges(*this); }
	};

	std::vector<int> get_shortest_paths(const std::vector<dijkstra::ivertex>& vertices, int src, int dest)
	{
		std::vector<int> dists(vertices.size(), -1);
		dists[src] = 0;

		using pair = std::pair<int, int>;
		std::priority_queue<pair, std::vector<pair>, std::greater<pair>> minv;
		minv.emplace(0, src);
		while (!minv.empty())
		{
			int dist = minv.top().first;
			int curr = minv.top().second;
			minv.pop();

			if (dists[curr] <= dist)
			{
				continue;
			}

			if (curr == dest)
			{
				return dists;
			}

			for (auto& e : vertices[curr].edges())
			{
				int next_dist = dist + e.dist();
				int next = e.dest();

				if (dists[next] > next_dist)
				{
					dists[next] = next_dist;
					minv.emplace(next_dist, next);
				}
			}
		}

		return dists;
	}

};

class edge : dijkstra::iedge
{
public:
	virtual int dist() const { return _dist; }
	virtual int dest() const { return _dest; }
private:
	int _dist, _dest;
};

class vertex : dijkstra::ivertex
{
public:
	virtual std::vector<dijkstra::iedge>::iterator begin() const { return edges.begin(}
private:
	std::vector<dijkstra::iedge> edges;
};

typedef std::pair<int,int> pair;

int num_city, num_road;
bool arrived[10000];
std::vector<pair> roads[10000];
std::priority_queue<pair, std::vector<pair>, std::greater<pair>> next;

int calc_min_dist();
int main( int argc, char** argv )
{
	int num_testcase;
	my::cin >> num_testcase;

	while( num_testcase-- )
	{
		my::cin >> num_city >> num_road;
		
		for( int i = 0; i < num_city; ++i )
		{
			arrived[i] = false;
			roads[i].clear();
		}
		std::priority_queue<pair, std::vector<pair>, std::greater<pair>> clear;
		next.swap(clear);

		for( int i = 0; i < num_road; ++i )
		{
			int city1, city2, dist;
			my::cin >> city1 >> city2 >> dist;

			roads[city1].push_back(pair(dist,city2));
			roads[city2].push_back(pair(dist,city1));
		}
		
		printf("%d\n", calc_min_dist());
	}

	return 0;
}

void add_city( int accum_dist, int city )
{
	arrived[city] = true;
	for( auto road : roads[city] )
	{
		if( !arrived[road.second] )
		{	
			next.push(pair(accum_dist+road.first, road.second));
		}
	}
}
int calc_min_dist()
{
	add_city( 0, 0 );
	
	while( next.size() > 0 )
	{
		pair curr = next.top();
		next.pop();

		if( arrived[curr.second] )
			continue;
		else if( curr.second == num_city-1 )
			return curr.first;
		else
			add_city( curr.first, curr.second );
	}

	return 0;
}

/*
10
7 14
0 1 3
0 2 10
0 3 9
3 4 4
3 5 16
3 1 12
1 2 4
1 2 10
1 4 3
1 5 10
5 4 9
4 6 4
5 6 16
2 6 30
*/