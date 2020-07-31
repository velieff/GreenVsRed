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
			std::cout << "Error: The symbol #" << i << " is different from 0 or 1!\n";
			return;
		}
	}

}

void Grid::changeColor(int X, int Y)
{
	cells[X][Y] = !cells[X][Y];
}

int Grid::countNeighboursHelper(int X, int Y, Cell color, bool isItInDifferentColumn) const
{
	if (X < 0 || X >= this->x)
	{
		return 0;
	}

	int count = 0;
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
	if (isItInDifferentColumn)
	{
		if (cells[X][Y] == color)
			count++;
	}

	return count;
}

int Grid::countNeighbours(int X, int Y, Cell color) const
{
	return countNeighboursHelper(X - 1, Y, color, true)
		 + countNeighboursHelper(X + 1, Y, color, true)
		 + countNeighboursHelper(X, Y, color, false);
}

bool Grid::rule1(int X, int Y, int greenNeighboursNum) const
{
	if (cells[X][Y] == Green)
	{
		return false;
	}
	return (greenNeighboursNum == 3 || greenNeighboursNum == 6);
}

bool Grid::rule3(int X, int Y, int greenNeighboursNum) const
{
	if (cells[X][Y] == Red)
	{
		return false;
	}
	return (greenNeighboursNum != 2 && greenNeighboursNum != 3 && greenNeighboursNum != 6);
}

int Grid::calculate(int X, int Y, int N)
{
	int result = 0;
	int countGreen = countNeighbours(X, Y, Green);
	for (int i = 0; i <= N; i++)
	{
		if (cells[X][Y] == Green)
		{
			result++;
		}

		if (rule1(X, Y, countGreen) || rule3(X, Y, countGreen))
		{
			changeColor(X, Y);
		}
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