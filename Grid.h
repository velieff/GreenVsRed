#pragma once

#include<iostream>
#include<string>

typedef bool Cell;
#define Red false
#define Green true

class Grid
{
private:
	int x;
	int y;
	Cell** cells;

public:
	Grid(int X, int Y);
	~Grid();
	Grid(const Grid& other);
	Grid& operator=(const Grid& other);
	
	int getX() const;
	int getY() const;
	void setLineY(int Y, std::string line);
	void changeColor(int X, int Y);
	int countNeighbours(int X, int Y, Cell color) const;
	bool rule1(int X, int Y, int greenNeighboursNum) const;
	//rule2 means the same as rule1
	bool rule3(int X, int Y, int greenNeighboursNum) const;
	//rule4 means the same as rule3
	int calculate(int X, int Y, int N);
	
private:
	int countNeighboursHelper(int X, int Y, Cell color, bool isItInTheSameColumn) const;
	void initialize();
	void setXY(int X, int Y);
	void copy(const Grid& other);
	void destroy();
};