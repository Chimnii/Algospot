#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>

const int least_pound = 50;

int get_maximum_trip(std::vector<int>& weights);

int main()
{
	std::ifstream fin;
	fin.open("HackerCup\\lazy_loading_input.txt");

	std::ofstream fout;
	fout.open("HackerCup\\lazy_loading_output.txt");

	int t;
	fin >> t;
	for (int i = 1; i <= t; ++i)
	{
		int n;
		fin >> n;

		std::vector<int> weights;
		while (n--)
		{
			int w;
			fin >> w;

			weights.emplace_back(w);
		}

		int trip = get_maximum_trip(weights);
		//std::cout << "Case #" << i << ": " << trip << std::endl;
		fout << "Case #" << i << ": " << trip << std::endl;
	}

	fin.close();
	fout.close();

	return 0;
}

int get_maximum_trip(std::vector<int>& weights)
{
	std::sort(weights.begin(), weights.end(), std::greater<int>());

	int trip = 0;

	int first = 0, last = -1 + weights.size();
	while (first <= last)
	{
		int top = weights[first];
		++first;

		int sum = top;
		while (sum < least_pound && first <= last)
		{
			--last;
			sum += top;
		}
		
		if (sum >= least_pound)
		{
			++trip;
		}
	}

	return trip;
}
