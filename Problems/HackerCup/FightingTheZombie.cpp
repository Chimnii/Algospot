#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

void get_spell_values(const std::string& spell, int& time, int& side, int& additive);
double get_prob(int side, int time, int sum);

int main()
{
	int t;
	std::cin >> t;

	for (int i = 1; i <= t; ++i)
	{
		int h, s;
		std::cin >> h >> s;

		double prob = 0.0;
		while (s--)
		{
			std::string spell;
			std::cin >> spell;

			int time, side, additive;
			get_spell_values(spell, time, side, additive);
			double current_prob = get_prob(side, time, std::max(time, h-additive));

			prob = std::max(prob, current_prob);
		}

		std::cout << "Case #" << i << ": " << prob << std::endl;
	}
}

void get_spell_values(const std::string& spell, int& time, int& side, int& additive)
{
	std::istringstream in(spell);

	char d;
	in >> time;
	in >> d;
	in >> side;
	if (in.eof()) additive = 0;
	else in >> additive;
}

double get_prob(int side, int time, int sum)
{
	double default_probs = 1.0 / side;

	std::vector<double> probs(side * time + 1);
	std::vector<double> next_probs(side * time + 1);
	probs[0] = 1.0;
	next_probs[0] = 1.0;

	for (int tried = 1; tried <= time; ++tried)
	{
		for (int num = tried; num <= side * tried; ++num)
		{
			next_probs[num] = 0.0;
		}

		for (int num = 1; num <= side; ++num)
		{
			for (int i = (tried - 1); i <= (tried - 1) * side; ++i)
			{
				next_probs[num+i] += probs[i] * default_probs;
			}
		}
		probs.swap(next_probs);
	}
	
	double prob = 0.0;
	for (int i = sum; i <= side * time; ++i)
	{
		prob += probs[i];
	}

	return prob;
}
