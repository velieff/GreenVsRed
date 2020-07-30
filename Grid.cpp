#include<iostream>
#include"Grid.h"

Grid::Grid(int X, int Y)
{
	setXY(X, Y);
	initialize();
}

Grid::~Grid()
{
	destroy();
}

Grid::Grid(const Grid& other)
{
	copy(other);
}

Grid& Grid::operator=(const Grid& other)
{
	if (this != &other)
	{
		destroy();
		copy(other);
	}
	return *this;
}

int Grid::getX() const
{
	return this->x;
}

int Grid::getY() const
{
	return this->y;
}

void Grid::setLineY(int Y, std::string line)
{
	if (line.length() != x)
	{
		std::cout << "Error: Length of the string is different from x!\n";
		return;
	}
	for (int i = 0; i < x; i++)
	{
		if (line[i] == '0')
		{
			cells[Y][i] = Red;
		}
		else if (line[i] == '1')
		{
			cells[Y][i] = Green;
		}
		else
		{
			std::cout << "Error: The symbol #"<<i<<" is different from 0 or 1!\n";
			return;
		}
	}

}

void Grid::changeColor(int X, int Y)
{
	cells[X][Y] = !cells[X][Y];
}

int Grid::countNeighbours(int X, int Y, Cell color) const
{
	int count = 0;
	if (X - 1 >= 0)
	{
		if (Y - 1 >= 0)
		{
			if (cells[X - 1][Y - 1] == color)
				count++;
		}
		if (Y + 1 < this->y)
		{
			if (cells[X - 1][Y + 1] == color)
				count++;
		}
		if (cells[X - 1][Y] == color)
			count++;
	}

	if (X + 1 < this->x)
	{
		if (Y - 1 >= 0)
		{
			if (cells[X + 1][Y - 1] == color)
				count++;
		}
		if (Y + 1 < this->y)
		{
			if (cells[X + 1][Y + 1] == color)
				count++;
		}
		if (cells[X + 1][Y] == color)
			count++;
	}

	if (Y - 1 >= 0)
	{
		if (cells[X][Y - 1] == color)
			count++;
	}

	if (Y + 1 < this->y)
	{
		if (cells[X][Y + 1] == color)
			count++;
	}

	return count;
}

void Grid::rule1(int X, int Y, int greenNeighboursNum)
{
	if (cells[X][Y] == Green)
	{
		return;
	}
	if (greenNeighboursNum == 3 || greenNeighboursNum == 6)
	{
		changeColor(X, Y);
	}
}

void Grid::rule3(int X, int Y, int greenNeighboursNum)
{
	if (cells[X][Y] == Red)
	{
		return;
	}
	if (greenNeighboursNum != 2 && greenNeighboursNum != 3 && greenNeighboursNum != 6)
	{
		changeColor(X, Y);
	}
}

int Grid::calculate(int X, int Y, int N)
{
	int result = 0;
	for (int i = 0; i <= N; i++)
	{
		if (cells[X][Y] == Green)
			result++;
		int countGreen = countNeighbours(X, Y, Green);
		rule1(X, Y, countGreen);
		rule3(X, Y, countGreen);
	}
	return result;
}

void Grid::initialize()
{
	cells = new Cell*[y];
	for (int i = 0; i < y; i++)
	{
		cells[i] = new Cell[x];
	}
}

void Grid::setXY(int X, int Y)
{
	this->x = X;
	this->y = Y;
}

void Grid::copy(const Grid& other)
{
	setXY(other.x, other.y);
	initialize();
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			this->cells[i][j] = other.cells[i][j];
		}
	}
}

void Grid::destroy()
{
	for (int i = 0; i < y; i++)
	{
		delete[] cells[i];
	}
	delete[] cells;
}