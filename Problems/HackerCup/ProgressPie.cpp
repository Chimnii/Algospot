#include <iostream>
#include <cmath>

const double pi = std::acos(-1);
const int center = 50;
const int radius = 50;

bool in_circle(int x, int y);
double rad_to_percentage(double rad);
double coord_to_percentage(int x, int y);

int main()
{
	int n;
	std::cin >> n;
	
	for (int i = 1; i <= n; ++i )
	{
		int percentage, x, y;
		std::cin >> percentage >> x >> y;

		bool black = false;

		if (in_circle(x, y))
		{
			if( percentage == 0 )
			{
				black = false;
			}
			else if( percentage == 100 )
			{
				black = true;
			}
			else
			{
				double coord_percentage = coord_to_percentage(x, y);

				black = (percentage >= coord_percentage);
			}
		}
		else
		{
			black = false;
		}

		std::cout << "Case #" << i << ": " << (black ? "black" : "white") << std::endl;
	}

	return 0;
}

bool in_circle(int x, int y)
{
	return (std::pow(x - radius, 2) + std::pow(y - center, 2) <= pow(radius, 2));
}

double rad_to_percentage(double rad)
{
	double radfromyaxis = 2.5 * pi - rad;
	double percentage = 50 * radfromyaxis / pi;

	while( percentage < 0 ) percentage += 100;
	while( percentage > 100 ) percentage -= 100;

	//std::cout << "angle:" << rad*180/pi << std::endl;
	//std::cout << "anglefromy:" << radfromyaxis*180/pi << std::endl;
	//std::cout << "percentage:" << percentage << std::endl;

	return percentage;
}

double coord_to_percentage(int x, int y)
{
	double rad = std::atan2(y - center, x - center);
	double percentage = rad_to_percentage(rad);

	return percentage;
}
