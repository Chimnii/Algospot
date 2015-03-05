#include <stdio.h>
#include <vector>

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

struct edge
{
	int start, dest;
	int dist;

	bool operator<( const edge& other ) const { return dist < other.dist; }
	bool operator>( const edge& other ) const { return dist > other.dist; }
};

struct vertex
{
	int id;
	int min_dist;
	long long num_paths;
	std::vector<edge> edges;
};

int num_vertex, num_edge, num_visit;
vertex vertices[101];

void calc_paths( int start, int dest );
void divide_fraction( long long& numerator, long long& denominator );
int main( int argc, char** argv )
{
	int num_testcase;
	my::cin >> num_testcase;

	while( num_testcase-- )
	{
		my::cin >> num_vertex >> num_edge >> num_visit;

		for( int i = 1; i <= num_vertex; ++i )
		{
			vertices[i].id = i;
			vertices[i].min_dist = -1;
			vertices[i].num_paths = 0;
			vertices[i].edges.clear();
		}

		for( int i = 1; i <= num_edge; ++i )
		{
			int start, dest, dist;
			my::cin >> start >> dest >> dist;

			edge e;
			e.start = start;
			e.dest = dest;
			e.dist = dist;
			vertices[start].edges.push_back(e);

			edge r_e;
			r_e.start = dest;
			r_e.dest = start;
			r_e.dist = dist;
			vertices[dest].edges.push_back(r_e);
		}

		for( int i = 1; i <= num_visit; ++i )
		{
			int visit_dest;
			my::cin >> visit_dest;

			calc_paths( 1, num_vertex );
			int visit_dist = vertices[visit_dest].min_dist;			
			int dest_dist = vertices[num_vertex].min_dist;
			long long visit_paths = vertices[visit_dest].num_paths;
			long long dest_paths = vertices[num_vertex].num_paths;

			calc_paths( num_vertex, 1 );
			int r_visit_dist = vertices[visit_dest].min_dist;
			long long r_visit_paths = vertices[visit_dest].num_paths;

			long long numerator, denominator;
			if( visit_dist + r_visit_dist == dest_dist )
			{
				numerator = visit_paths * r_visit_paths;
				denominator = dest_paths;
			}
			else
			{
				numerator = 0;
				denominator = 1;
			}

			divide_fraction( numerator, denominator );
			printf( "%lld/%lld\n", numerator, denominator );
		}
	}

	return 0;
}

#include <queue>
typedef std::priority_queue<edge, std::vector<edge>, std::greater<edge>> edge_queue;
edge_queue nearest_edges;

void set_vertex( int current )
{
	for( auto it = vertices[current].edges.begin(); it != vertices[current].edges.end(); ++it )
	{
		int dest = it->dest;
		int dist = vertices[current].min_dist + it->dist;
		if( vertices[dest].min_dist == -1 || vertices[dest].min_dist >= dist )
		{
			edge e;
			e.start = current;
			e.dest = dest;
			e.dist = dist;
			nearest_edges.push(e);
			//printf("nearest_vertex added : id=%d, min_dist=%d, num_paths=%d\n", dest, dist, vertices[current].num_paths );
		}
	}
}

void calc_paths( int start, int dest )
{
	for( int i = 1; i <= num_vertex; ++i )
	{
		vertices[i].min_dist = -1;
		vertices[i].num_paths = 0;
	}
	nearest_edges = edge_queue();

	vertices[start].min_dist = 0;
	vertices[start].num_paths = 1;
	set_vertex( start );

	while( nearest_edges.size() > 0 )
	{
		edge nearest = nearest_edges.top(); nearest_edges.pop();

		if( vertices[nearest.dest].min_dist == -1 )
		{
			vertices[nearest.dest].min_dist = nearest.dist;
			vertices[nearest.dest].num_paths = vertices[nearest.start].num_paths;
			//printf( "set_vertex : start=%d dest=%d, dist=%d, num_paths=%d\n", nearest.start, nearest.dest, nearest.dist, vertices[nearest.dest].num_paths );
			set_vertex(nearest.dest);
		}
		else if( vertices[nearest.dest].min_dist == nearest.dist )
		{
			//printf( "add_paths : start=%d dest=%d, dist=%d, num_paths=%d+%d\n", nearest.start, nearest.dest, nearest.dist, vertices[nearest.dest].num_paths, vertices[nearest.start].num_paths );
			vertices[nearest.dest].num_paths += vertices[nearest.start].num_paths;
		}

		if( vertices[dest].min_dist != -1 && nearest.dist > vertices[dest].min_dist )
		{
			break;
		}
	}
}

long long  getGCD( long long  n1, long long  n2 )
{
	while( n1 != n2 )
	{
		if( n2 > n1 )
			n2 = n2 - n1;
		else
			n1 = n1 - n2;
	}

	return n1;
}

void divide_fraction( long long& numerator, long long& denominator )
{
	if( numerator > 1 )
	{
		long long GCD = getGCD( numerator, denominator );
		numerator /= GCD;
		denominator /= GCD;
	}
}