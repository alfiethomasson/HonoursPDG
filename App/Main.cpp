#include <iostream>
#include "Grid.h"
#include <random>

using namespace std;


int main(int argc, char** argv)
{
	cout << "Hi!  Welcome to the Drunkward Walk simple map creator." << endl;
	int width = 100	;
	int height = 100;
	Grid *map = new Grid(width, height);
	int *rd = map->GetRandomPoint();
	//std::cout << point[0] << ", " << point[1] << endl;
	int point[2];
	point[0] = rd[0];
	point[1] = rd[1];

	std::random_device random;
	std::mt19937 gen(random());
	std::uniform_int_distribution<> dir(0, 3);

	std::cout << "Beginning drunkard walk" << std::endl;

	for (int i = 0; i < 5000; i++)
	{
		int direction = dir(gen);
		switch (direction)
		{
		//North
		case 0:
			//std::cout << "North" << endl;
			if (point[1] != 0)
			{
				//std::cout << point[0] << ", " << point[1] << endl;
				map->FillPoint(point[0], point[1] - 1);
				point[1] -= 1;
			}
			else
			{
				i--;
				break;
			}
			break;
			
		//East	
		case 1:
		//	std::cout << "East" << endl;
			if (point[0] != 0)
			{
			//	std::cout << point[0] << ", " << point[1] << endl;
				map->FillPoint(point[0] - 1, point[1]);
				point[0] -= 1;
			}
			else
			{
				i--;
				break;
			}
			break;
		//South
		case 2:
			//std::cout << "South" << endl;
			if (point[1] != map->Height)
			{
				//std::cout << point[0] << ", " << point[1] << endl;
				map->FillPoint(point[0], point[1] + 1);
				point[1] += 1;
			}
			else
			{
				i--;
				break;
			}
			break;
		//West
		case 3:
			//std::cout << "West" << endl;
			if (point[0] != map->Width)
			{
				//std::cout << point[0] << ", " << point[1] << endl;
				map->FillPoint(point[0] + 1, point[1]);
				point[0] += 1;
			}
			else
			{
				i--;
				break;
			}
			break;
		}
	}

	map->Print();
	// Return 0 (OK)
	return 0;
}