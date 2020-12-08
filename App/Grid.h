#pragma once
#include <vector>

class Grid
{
public: 
	Grid(int width, int height);
	~Grid();

	int* GetRandomPoint();
	void EmptyPoint(int x, int y);
	void FillPoint(int x, int y);

	void Print();

	int Width;
	int Height;

protected:
	std::vector<std::vector<char>> mapVector;
};