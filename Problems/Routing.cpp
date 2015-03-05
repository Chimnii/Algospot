#include <iostream>
#include <vector>
#include <iomanip>

struct CPath
{
	int destIndex;
	double amp;
};

struct CComputer
{
	enum EState
	{
		CALCULATED,
		CALCULATING,
		UNCALCULATED
	};
	int index;
	int state;
	double minimumAmp;
	std::vector<CPath> paths;
};

CComputer computers[10000];

void CalcMinimumAmp( const int startIndex, const int lastIndex );

int main( int argc, char** argv )
{
	int numTestCase;
	std::cin >> numTestCase;

	while( numTestCase-- )
	{
		int numComputer, numPath;
		std::cin >> numComputer >> numPath;

		for( int i = 0; i < numComputer; ++i )
		{
			computers[i].index = i;
			computers[i].state = CComputer::UNCALCULATED;
			computers[i].minimumAmp = -1;
			computers[i].paths.clear();
		}

		for( int i = 0; i < numPath; ++i )
		{
			int start, dest;
			double amp;
			std::cin >> start >> dest >> amp;

			CPath path;
			path.destIndex = dest;
			path.amp = amp;
			computers[start].paths.push_back(path);

			path.destIndex = start;
			path.amp = amp;
			computers[dest].paths.push_back(path);
		}

		CalcMinimumAmp( 0, numComputer - 1 );
		std::cout << std::fixed << std::setprecision(10) << computers[numComputer-1].minimumAmp << std::endl;
	}

	return 0;
}

void CalcMinimumAmp( const int startIndex, const int lastIndex )
{
	std::vector<int> calculating;
	
	computers[0].minimumAmp = 1;
	computers[0].state = CComputer::CALCULATING;
	calculating.push_back(0);

	while( !calculating.empty() )
	{
		int minComputerIndex = 0;
		double minComputerAmp = 0;

		std::vector<int>::iterator it = calculating.begin();
		while( it != calculating.end() )
		{
			if( computers[*it].state == CComputer::CALCULATED )
			{
				it = calculating.erase(it);
			}
			else
			{
				if( minComputerAmp == 0 || computers[*it].minimumAmp < minComputerAmp )
				{
					minComputerIndex = *it;
					minComputerAmp = computers[*it].minimumAmp;
				}
				++it;
			}
		}

		computers[minComputerIndex].state = CComputer::CALCULATED;

		for( std::vector<CPath>::iterator pathIt = computers[minComputerIndex].paths.begin(); pathIt != computers[minComputerIndex].paths.end(); ++pathIt )
		{
			double newAmp = computers[minComputerIndex].minimumAmp * pathIt->amp;
			if( computers[ pathIt->destIndex ].state == CComputer::CALCULATED )
			{
				continue;
			}
			else if( computers[ pathIt->destIndex ].state == CComputer::CALCULATING )
			{	
				if( computers[ pathIt->destIndex ].minimumAmp > newAmp )
				{
					computers[ pathIt->destIndex ].minimumAmp = newAmp;
				}
			}
			else
			{
				computers[ pathIt->destIndex ].minimumAmp = newAmp;
				computers[ pathIt->destIndex ].state = CComputer::CALCULATING;
				calculating.push_back( pathIt->destIndex );
			}
		}

		if( minComputerIndex == lastIndex )
		{
			return;
		}
	}
}
