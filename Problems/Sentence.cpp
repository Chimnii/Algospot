#include <iostream>
#include <string>
#include <limits>

int main( int argc, char** argv )
{
	int numSentence, numMemo;
	std::cin >> numSentence >> numMemo;
	std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n'); 
	
	std::string sentences[1000], memos[10000];
	for( int i = 0; i < numSentence; ++i )
	{
		std::getline(std::cin, sentences[i]);
	}
	for( int i = 0; i < numMemo; ++i )
	{
		std::getline(std::cin, memos[i]);
	}

	int answer = 0;
	for( int mi = 0; mi < numMemo; ++mi )
	{
		for( int si = 0; si < numSentence; ++si )
		{
			bool isCorrect = true;
			std::string::iterator memo_it = memos[mi].begin();
			std::string::iterator sentence_it = sentences[si].begin();
			while(true)
			{
				if( memo_it == memos[mi].end() )
				{
					break;
				}

				if( sentence_it == sentences[si].end() )
				{
					isCorrect = false;
					break;
				}

				if( *memo_it != *sentence_it )
				{
					isCorrect = false;
					break;
				}

				++memo_it;
				++sentence_it;
			}

			if( isCorrect )
			{
				++answer;
				break;
			}
		}
	}

	std::cout << answer;
}