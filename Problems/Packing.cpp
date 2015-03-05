#include <stdio.h>
#include <string>
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

	inline bool is_char( char c ){ return ( c > ' '  ); }
	inline istream& operator>>( istream& in, char* out )
	{
		char c;
		while( c = getchar() ){ if( is_char(c) ){ *out = c; ++out; break; } }
		while( c = getchar() ){ if( !is_char(c) ) break; *out = c; ++out; }
		*out = 0;
		return in;
	}

	inline istream& operator>>( istream&in, std::string& out )
	{
		static char temp[21];
		operator>>( in, temp );
		out = temp;
		return in;
	}
}

struct accum_data
{
	int accum_weight;
	int accum_value;
	std::vector<std::string> object_names;
	accum_data() : accum_weight(0), accum_value(0) {}
};
accum_data init;

int num_object, carrier_size;
std::vector<accum_data> cached(1001);

int main( int argc, char** argv )
{
	int num_testcase;
	my::cin >> num_testcase;

	while( num_testcase-- )
	{
		my::cin >> num_object >> carrier_size;

		cached.clear();
		cached.resize(1001);

		int max_value = 0, max_value_weight;
		for( int i = 0 ; i < num_object; ++i )
		{
			int curr_weight, curr_value;
			std::string curr_name;
			my::cin >> curr_name >> curr_weight >> curr_value;

			std::vector<accum_data> added;
			for( int i = 0; i <= carrier_size; ++i )
			{
				if( i != 0 && cached[i].accum_value == 0 )
				{
					continue;
				}

				int weight = cached[i].accum_weight + curr_weight;
				int value = cached[i].accum_value + curr_value;

				if( weight > carrier_size )
				{
					break;
				}

				if( cached[weight].accum_value < value )
				{
					accum_data data;
					data.accum_weight = weight;
					data.accum_value = value;
					data.object_names = cached[i].object_names;
					data.object_names.push_back(curr_name);
					added.push_back(data);
				}
			}

			for( auto it = added.begin(); it != added.end(); ++it )
			{
				int weight = it->accum_weight;
				cached[weight] = *it;
				if( max_value < cached[weight].accum_value )
				{
					max_value = cached[weight].accum_value;
					max_value_weight = cached[weight].accum_weight;
				}
			}
		}

		auto& data = cached[max_value_weight];
		printf( "%d %d\n", max_value, data.object_names.size() );
		for( auto name = data.object_names.begin(); name != data.object_names.end(); ++name )
		{
			printf( "%s\n", name->c_str() );
		}
	}

	return 0;
}
