#include "Grid.h"
#include <random>
#include <iostream>
#include <ctime>

Grid::Grid(int width, int height)
{
	Width = width - 1;
	Height = height - 1;
	for (int i = 0; i < height; i++)
	{
		mapVector.push_back(std::vector<bool>());
		for (int w = 0; w < width; w++)
		{
			mapVector[i].push_back(false);
		}
	}
}

int* Grid::GetRandomPoint()
{
	std::random_device random;
	std::mt19937 gen(random());
	std::uniform_int_distribution<> w(0, Width), h(0, Height);
	int randPoint[2];
	randPoint[0] = w(gen);
	randPoint[1] = h(gen);
	return randPoint;
}

void Grid::EmptyPoint(int x, int y)
{
	mapVector[x][y] = false;
}

void Grid::FillPoint(int x, int y)
{
	mapVector[x][y] = true;
}

void Grid::Print()
{
	for (int i = 0; i < Height + 1; i++)
	{
		for (int y = 0; y < Width + 1; y++)
		{
			//std::cout << mapVector[i][y];
		}
	}
}

bool Grid::GetPoint(int x, int y)
{
	return mapVector[x][y];
}

void Grid::InitRandom(float cutoff)
{
	srand(1000);

	for (int x = 0; x < Width + 1; x++)
	{
		for (int y = 0; y < Height + 1; y++)
		{
			if (((double)rand() / RAND_MAX) < cutoff)
			{
				//std::cout << "Filling as true" << std::endl;
				mapVector[x][y] = true;
			}
			else
			{
				//std::cout << "Filling as false" << std::endl;
				mapVector[x][y] = false;
			}
		}
	}
}

void Grid::SetTestVal(int val)
{
	testVal = val;
}

int Grid::GetTestVal()
{
	return testVal;
}