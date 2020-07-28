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
	void rule1(int X, int Y, int greenNeighboursNum);
	//rule2 means the same as rule1
	void rule3(int X, int Y, int greenNeighboursNum);
	//rule4 means the same as rule3
	int calculate(int X, int Y, int N);
	
private:
	void initialize();
	void setXY(int X, int Y);
	void copy(const Grid& other);
	void destroy();
};