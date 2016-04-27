#include <iostream>
#include <string>

int main( int argc, char** argv )
{
	int i, n;
	char note[8];
	enum etype { ASC, DSC, MIX, MAX } type;
	std::string typestr[MAX] = { "ascending", "descending", "mixed" };

	i = 0;
	type = MAX;
	while( std::cin >> n )
	{
		note[i] = n;
		if( i > 0 && type != MIX )
		{
			etype newtype = (note[i] > note[i-1] ? ASC : DSC);
			type = (type == MAX ? newtype : (type != newtype ? MIX : type));
		}
		++i;
		
		if( i == 8 )
		{
			std::cout << typestr[type] << std::endl;
			i = 0;
			type = MAX;
		}
	}

	return 0;
}
