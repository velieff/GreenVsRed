#include<iostream>
#include<string>
#include"Grid.h"

int main()
{
	int x, y;
	std::cin >> x >> y;
	Grid g(x, y);

	std::string line;
	for (int i = 0; i < g.getY(); i++)
	{
		std::cin >> line;
		g.setLineY(i, line);
	}

	int x1, y1, n;
	std::cin >> x1 >> y1 >> n;
	std::cout << "Result: " << g.calculate(x1, y1, n) << '\n';
	return 0;
}