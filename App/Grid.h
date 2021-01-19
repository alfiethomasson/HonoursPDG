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
	void InitRandom(float randValue);
	bool GetPoint(int x, int y);

	void SetTestVal(int val);
	int GetTestVal();

	void Print();

	int Width;
	int Height;

protected:
	std::vector<std::vector<bool>> mapVector;
	int testVal;
};