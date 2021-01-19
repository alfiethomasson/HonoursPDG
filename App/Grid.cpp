#include "Grid.h"
#include <random>
#include <iostream>

Grid::Grid(int width, int height)
{
	Width = width - 1;
	Height = height - 1;
	for (int i = 0; i < height; i++)
	{
		mapVector.push_back(std::vector<char>());
		for (int w = 0; w < width; w++)
		{
			mapVector[i].push_back('O');
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
	std::cout << "Rand point 0 = " << randPoint[0] << std::endl;
	randPoint[1] = h(gen);
	std::cout << "Rand point 1 = " << randPoint[1] << std::endl;
	std::cout << "Calculated random point as: " << randPoint[0] << ", " << randPoint[1] << std::endl;
	return randPoint;
}

void Grid::EmptyPoint(int x, int y)
{
	mapVector[x][y] = 'O';
}

void Grid::FillPoint(int x, int y)
{
	mapVector[x][y] = ' ';
}

void Grid::Print()
{
	for (int i = 0; i < Height + 1; i++)
	{
		for (int y = 0; y < Width + 1; y++)
		{
			std::cout << mapVector[i][y];
		}
		std::cout << std::endl;	
	}
	std::cout << std::endl;
}