#include "Generator.h"
#include <random>
#include <math.h> 
#include "Delaunator.hpp"

sf::Image Generator::GenerateDungeon(int caMap[], int iterations, int type)
{
	//pixels.create(xSize, ySize, sf::Color::Black);

	//Grid map = new Grid(xSize, ySize);
	Grid *map = new Grid(xSize, ySize);
	//int *rd = map->GetRandomPoint();

	if (type == 0)
	{
		//std::random_device random;
		//std::mt19937 gen(random());
		//std::uniform_int_distribution<> w(0, map->Width), h(0, map->Height);

		int ran1 = rand() % map->Width;
		int ran2 = rand() % map->Height;
		int randPoint[2];
		randPoint[0] = ran1;
		std::cout << "Rand point 0 = " << randPoint[0] << std::endl;
		randPoint[1] = ran2;
		std::cout << "Rand point 1 = " << randPoint[1] << std::endl;
		std::cout << "Calculated random point as: " << randPoint[0] << ", " << randPoint[1] << std::endl;
		std::cout << "here" << std::endl;
		//std::cout << rd[0] << ", " << rd[1] << std::endl;
		int point[2];
		point[0] = randPoint[0];
		point[1] = randPoint[1];
		std::cout << point[0] << ", " << point[1] << std::endl;

		std::uniform_int_distribution<> dir(0, 3);

		for (int i = 0; i < iterations; i++)
		{
			//std::cout << "here" << std::endl;
			int direction = rand() % 3;
			switch (direction)
			{
				//North
			case 0:
				//std::cout << "North" << endl;
				if (point[1] != 0)
				{
					//std::cout << point[0] << ", " << point[1] << endl;
					//map->FillPoint(point[0], point[1] - 1);
					unsigned int point0 = point[0];
					//std::cout << point0 << std::endl;
					pixels.setPixel(point[0], point[1] - 1, sf::Color::White);
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
						//map->FillPoint(point[0] - 1, point[1]);
					pixels.setPixel(point[0] - 1, point[1], sf::Color::White);
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
					//map->FillPoint(point[0], point[1] + 1);
					pixels.setPixel(point[0], point[1] + 1, sf::Color::White);
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
					//map->FillPoint(point[0] + 1, point[1]);
					pixels.setPixel(point[0] + 1, point[1], sf::Color::White);
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
	}
	else
	{
		float aliveChance = 0.42f;
		int starvationLimit = 0;
		int overpopLimit = 0;
		int birthNumber = 4;
		int iter = 2;

		int deathLimit = 3;

		map->InitRandom(aliveChance);

		//Grid* newMap = new Grid(xSize, ySize);

		std::cout << "map test Val = " << map->GetTestVal() << std::endl;
		for (int i = 0; i < iter; i++)
		{
			//std::cout << "Doing iteration!" << std::endl;
			//std::cout << "map test Val = " << map->GetTestVal() << std::endl;
			//map = CAIteration(map, deathLimit, birthNumber);
		}
		std::cout << "map test Val = " << map->GetTestVal() << std::endl;
		for (int i = 0; i < xSize; i++)
		{
			for (int y = 0; y < ySize; y++)
			{
				if (map->GetPoint(i, y))
				{
					//pixels.setPixel(i, y, sf::Color::White);
				}
			}
		}

	}

	return pixels;

//map->Print();
}

void Generator::Reset(int x, int y, int alivePercent)
{
	float aliveChance = (float)alivePercent / 100;
	stepMap = new Grid(x, y);
	stepMap->InitRandom(aliveChance);
	stepRoot = new Node();
	totalBSPIterations = 0;
	stepRooms.clear();
	bounceStep = 0;
}

std::vector<std::vector<int>> Generator::GenerateMapTiles(int x, int y, int AlivePercent, int BirthNum, int iterations, int DeathLimit, int type, bool stepBool, int numberIterations)
{

	//pixels.create(xSize, ySize, sf::Color::Black);

	//Grid map = new Grid(xSize, ySize);
	Grid* map = new Grid(x, y);
	//int *rd = map->GetRandomPoint();

	int cutOff = 0.42;

	std::vector<std::vector<int>> vecMap;
		for (int i = 0; i < x; i++)
		{
			std::vector<int> row;
			for (int r = 0; r < y; r++)
			{
				if (((double)rand() / RAND_MAX) < cutOff)
				{
					row.push_back(0);
				}
				else
				{
					row.push_back(1);
				}
			}
			vecMap.push_back(row);
		}

	if (type == 0)
	{
		std::random_device random;
		std::mt19937 gen(random());
		std::uniform_int_distribution<> w(0, map->Width), h(0, map->Height);


		int ran1 = rand() % map->Width;
		int ran2 = rand() % map->Height;
		int randPoint[2];
		randPoint[0] = ran1;
		std::cout << "Rand point 0 = " << randPoint[0] << std::endl;
		randPoint[1] = ran2;
		std::cout << "Rand point 1 = " << randPoint[1] << std::endl;
		std::cout << "Calculated random point as: " << randPoint[0] << ", " << randPoint[1] << std::endl;
		std::cout << "here" << std::endl;
		//std::cout << rd[0] << ", " << rd[1] << std::endl;
		int point[2];
		point[0] = randPoint[0];
		point[1] = randPoint[1];
		std::cout << point[0] << ", " << point[1] << std::endl;

		std::uniform_int_distribution<> dir(0, 3);

		for (int i = 0; i < iterations; i++)
		{
			//std::cout << "here" << std::endl;
			int direction = rand() % 3;
			switch (direction)
			{
				//North
			case 0:
				//std::cout << "North" << endl;
				if (point[1] != 0)
				{
					//std::cout << point[0] << ", " << point[1] << endl;
					//map->FillPoint(point[0], point[1] - 1);
					unsigned int point0 = point[0];
					//std::cout << point0 << std::endl;
					//pixels.setPixel(point[0], point[1] - 1, sf::Color::White);
					//row.
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
						//map->FillPoint(point[0] - 1, point[1]);
					//pixels.setPixel(point[0] - 1, point[1], sf::Color::White);
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
					//map->FillPoint(point[0], point[1] + 1);
					//pixels.setPixel(point[0], point[1] + 1, sf::Color::White);
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
					//map->FillPoint(point[0] + 1, point[1]);
					//pixels.setPixel(point[0] + 1, point[1], sf::Color::White);
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
	}
	else
	{
		float aliveChance = (float)AlivePercent / 100;
		int starvationLimit = 0;
		int overpopLimit = 0;
		int birthNumber = BirthNum;
		int iter = iterations;

		int deathLimit = DeathLimit;

		std::cout << "Alive Chance = " << aliveChance << std::endl;
		std::cout << "Birth Num = " << birthNumber << std::endl;
		std::cout << "Iterations = " << iter << std::endl;
		std::cout << "Death Limit = " << deathLimit << std::endl;

		if (!stepBool)
		{
			map->InitRandom(aliveChance);
		}
		else
		{
			map = stepMap;
		}
			//Grid* newMap = new Grid(xSize, ySize);

		//	std::cout << "Size of vector before = " << vecMap.size() << std::endl;
			for (int i = 0; i < numberIterations; i++)
			{
				//std::cout << "Doing iteration!" << std::endl;
				//std::cout << "map test Val = " << map->GetTestVal() << std::endl;
				map = CAIteration(map, vecMap, deathLimit, birthNumber, x, y);
			}
			stepMap = map;
			//std::cout << "map test Val = " << map->GetTestVal() << std::endl;
			for (int i = 0; i < x; i++)
			{
				for (int r = 0; r < y; r++)
				{
					if (map->GetPoint(i, r))
					{
						//	std::cout << "Trying to make 1" << std::endl;
						vecMap[i][r] = 0;
					}
				}
			}
		}


	//std::cout << "map test Val = " << "GOT2HERE!" << std::endl;

	return vecMap;
}

Grid* Generator::CAIteration(Grid* oldMap, std::vector<std::vector<int>> tileMap, int deathLimit, int birthNumber, int xVal, int yVal)
{
	//std::cout << "Size of vector after = " << tileMap.size() << std::endl;
	Grid* newMap = new Grid(xVal, yVal);
	newMap->SetTestVal(10);
	for (int x = 0; x < xVal; x++)
	{
		for (int y = 0; y < yVal; y++)
		{
			//std::cout << "Co-ords = " << x << ", " << y << std::endl;
			int neighbours = countAliveNeighbours(oldMap, x, y, xVal, yVal);
			//std::cout << "After neighbours " << std::endl;
			//std::cout << "neighbours = " << neighbours << std::endl;
			//if (x == 10)
			//{
			////	std::cout << "Point at x = " << x << ", Alive = " << oldMap->GetPoint(x, y);
			//}

			if (oldMap->GetPoint(x, y))
			{
				//std::cout << "Filled" << std::endl;
				if (neighbours < deathLimit)
				{
					newMap->EmptyPoint(x, y);
					//tileMap[x][y] = 0;
					//pixels.setPixel(x, y, sf::Color::Black);
				}
				else
				{
					newMap->FillPoint(x, y);
					//tileMap[x][y] = 1;
					//pixels.setPixel(x, y, sf::Color::White);
				}
			}
			else
			{
			//	std::cout << "Not Filled " << std::endl;
				if (neighbours > birthNumber)
				{
					newMap->FillPoint(x, y);
					//tileMap[x][y] = 1;
					//pixels.setPixel(x, y, sf::Color::White);
				}
				else
				{
					newMap->EmptyPoint(x, y);
					//tileMap[x][y] = 0;
					//pixels.setPixel(x, y, sf::Color::Black);
				}
			}
		}
	}

	return newMap;
}

 int Generator::countAliveNeighbours(Grid* map, int x, int y, int xVal, int yVal) {
	int count = 0;
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			int neighbour_x = x + i;
			int neighbour_y = y + j;
			//If we're looking at the middle point
			if (i == 0 && j == 0) {
				//Do nothing, we don't want to add ourselves in!
			}
			//In case the index we're looking at it off the edge of the map
			else if (neighbour_x < 0 || neighbour_y < 0 || neighbour_x >= xVal || neighbour_y >= yVal) {
				count = count + 1;
			}
			//Otherwise, a normal check of the neighbour
			else if (map->GetPoint(neighbour_x, neighbour_y)) {
				count = count + 1;
			}
		}
	}
	return count;
}

 std::vector<std::vector<int>> Generator::GenerateBSP(int depthMax, int SizeInt, int minHor, int maxHor, int minVer, int maxVer, bool stepActive, int stepDepth)
{

	 std::cout << "X val = " << SizeInt << std::endl;
	 std::cout << "Y val = " << SizeInt << std::endl;


	Grid* map = new Grid(SizeInt, SizeInt);
	std::vector<std::vector<int>> mapOutput;
	for (int i = 0; i < SizeInt; i++)
	{
		std::vector<int> row;
		//row.reserve(32);
		for (int y = 0; y < SizeInt; y++)
		{
			row.push_back(1);
		}
		mapOutput.push_back(row);
	}

	Node* root = new Node();
	if (stepActive)
	{
		root = stepRoot;
	}
	else
	{
		totalBSPIterations = depthMax;
	}


	std::cout << "Min Hor Before = " << minHor << std::endl;

	float minHorMod = (float)minHor / 100;
	float maxHorMod = (float)maxHor / 100;
	float minVerMod = (float)minVer / 100;
	float maxVerMod = (float)maxVer / 100;

	std::cout << "Min Hor = " << minHorMod << std::endl;

	rooms.clear();

	root->row = 0;
	root->column = 0;
	root->width = SizeInt;
	root->height = SizeInt;


	int depth = 0;
	if (depth < stepDepth)
	{
		Split(root, 0, depthMax, SizeInt, minHorMod, maxHorMod, minVerMod, maxVerMod, totalBSPIterations, stepActive);
	}
	totalBSPIterations += stepDepth;
	stepRoot = root;

	//mapOutput = CreateHall(root, mapOutput);

	//sf::Image img = GenerateImageBSP();
	std::vector<std::vector<int>> returnedMap = GenerateBSPOutput(mapOutput);

	//int random = r(gen);
	//if (r(gen) == 0)
	//{
	//	std::uniform_int_distribution<int> w(xSize * 0.4, ySize * 0.6);

	//}
	//else
	//{

	//}
	return returnedMap;

}

 std::vector<std::vector<int>> Generator::AddCorridors(int SizeInt)
 {
	 std::vector<std::vector<int>> mapOutput;
	 for (int i = 0; i < SizeInt; i++)
	 {
		 std::vector<int> row;
		 //row.reserve(32);
		 for (int y = 0; y < SizeInt; y++)
		 {
			 row.push_back(1);
		 }
		 mapOutput.push_back(row);
	 }

	 mapOutput = CreateHall(stepRoot, mapOutput);

	 std::vector<std::vector<int>> returnedMap = BSPRandomRooms(mapOutput);

	 return returnedMap;
 }

void Generator::Split(Node* node, int depth, int maxDepth, int SizeInt, float minHor, float maxHor, float minVer, float maxVer, int totalIterations, bool doAll)
{

	std::cout << "Depth = " << depth << std::endl;
	//std::cout << "totalIter = " << totalIterations << std::endl;
		std::cout << "Test" << std::endl;
	if (depth == totalIterations || !doAll)
	{
		node->A = new Node();
		node->B = new Node();

		int split;
		int splitTemp = rand() % 1;
		//std::cout << "Split before: " << splitTemp << std::endl;
		if (node->parentSplit == splitTemp)
		{
			if ((rand() % 100) < 90)
			{
				std::cout << "Swapping Split" << std::endl;
				split = !node->parentSplit;
			}
			else
			{
				std::cout << "Not Swapping Split" << std::endl;
				split = splitTemp;
			}
		}
		else
		{
			split = splitTemp;
		}
		//std::cout << "Split after: " << split << std::endl;

		node->A->parentSplit = split;
		node->B->parentSplit = split;

		if (split)
		{
			int min = (int)(minVer * node->height);
			int max = (int)(maxVer * node->height);
			//std::cout << "Horizontal split" << std::endl;
			int rowLine = ((rand() % (max - min + 1)) + min);
			node->A->row = node->row;
			node->A->column = node->column;
			node->A->width = node->width;
			node->A->height = (((node->A->row + rowLine) + 1) - node->A->row);

			node->B->row = (node->A->row + (rowLine + 1));
			node->B->column = node->column;
			node->B->width = node->width;
			node->B->height = (node->height - node->A->height);
		}
		else
		{
			//std::cout << "Vertical split" << std::endl;
			int min = (int)(minHor * node->width);
			int max = (int)(maxHor * node->width);
			int colLine = ((rand() % (max - min + 1)) + min);
			node->A->row = node->row;
			node->A->column = node->column;
			node->A->width = (((node->A->column + colLine) + 1) - node->A->column);
			node->A->height = node->height;

			node->B->row = node->row;
			node->B->column = (node->A->column + (colLine + 1));
			node->B->width = (node->width - node->A->width);
			node->B->height = node->height;
		}
		rooms.push_back(node->A);
		rooms.push_back(node->B);
	}
	if(depth < totalIterations)
	{
		std::cout << "Depth smaller" << std::endl;
		if (depth < maxDepth) {
			std::cout << "Trying to split" << std::endl;
			this->Split(node->A, (depth + 1), maxDepth, SizeInt, minHor, maxHor, minVer, maxVer, totalIterations, doAll);
			this->Split(node->B, (depth + 1), maxDepth, SizeInt, minHor, maxHor, minVer, maxVer, totalIterations, doAll);
		}
	}
}

sf::Image Generator::GenerateImageBSP()
{
	pixels.create(xSize, ySize, sf::Color::Black);

	for (int i = 0; i < rooms.size(); i++)
	{
		Node* node = rooms[i];
		//std::cout << "Got a room here: " << i << std::endl;
		//pixels.setPixel(rooms[i]->row, rooms[i]->column, sf::Color::White);
		sf::Color color = sf::Color((rand() % 256), (rand() % 256), (rand() % 256));
		for (int r = node->row; r < (node->row + node->height); r++)
		{
			for (int c = node->column; c < (node->column + node->width); c++)
			{
				pixels.setPixel(r, c, color);
			}
		}
	}

	return pixels;
}

std::vector<std::vector<int>> Generator::GenerateBSPOutput(std::vector<std::vector<int>> map)
{
	for (int i = 0; i < rooms.size(); i++)
	{
		Node* node = rooms[i];

		int roomX = node->row + node->height;
		int roomY = node->column + node->width;

		//int randomX = rand() % roomX + (node->row + 1);
		//int randomY = rand() % roomY + (node->column + 1);

		std::cout << "Adding room!" << std::endl;
		for (int r = node->row + 1; r < (node->row + node->height); r++)
		{
			for (int c = node->column + 1; c < (node->column + node->width); c++)
			{
				//std::cout << "Adding tile thing at R: " << r << " , C: " << c << std::endl;
				map[r][c] = 0;
			}
		}

		//for (int r = node->row + 1; r < randomX; r++)
		//{
		//	for (int c = node->column + 1; c < randomY; c++)
		//	{
		//		//std::cout << "Adding tile thing at R: " << r << " , C: " << c << std::endl;
		//		map[r][c] = 0;
		//	}
		//}
	}

	return map;

}

std::vector<std::vector<int>> Generator::BSPRandomRooms(std::vector<std::vector<int>> map)
{

	std::cout << "Room size: " << rooms.size() << std::endl;

	for (int i = 0; i < rooms.size(); i++)
	{
		Node* node = rooms[i];

		int roomX = node->height;
		int roomY = node->width;

		int halfX = node->height / 2;
		int halfY = node->width / 2;

		int randomX = rand() % (node->height - halfX);
		int randomY = rand() % (node->width - halfY);

		if (randomX < 2)
		{
			randomX = 2;
		}
		if (randomY < 2)
		{
			randomY = 2;
		}

	//	randomX += 3;
		//randomY += 3;

		//std::cout << "Adding room!" << std::endl;
		for (int r = (node->row + halfX - randomX); r < (node->row + halfX + randomX); r++)
		{
			for (int c = (node->column + halfY - randomY); c < (node->column + halfY + randomY); c++)
			{
				//std::cout << "Adding tile thing at R: " << r << " , C: " << c << std::endl;
				map[r][c] = 0;
			}
		}

		std::cout << "Row & Height: " << node->row << ", " << node->height << std::endl;
		std::cout << "Column & Width: " << node->column << ", " << node->width << std::endl;

		std::cout << "Random X + Y: " << randomX << " , " << randomY << std::endl;

		//for (int r = node->row + 1; r < randomX; r++)
		//{
		//	for (int c = node->column + 1; c < randomY; c++)
		//	{
		//		//std::cout << "Adding tile thing at R: " << r << " , C: " << c << std::endl;
		//		tempMap[r][c] = 0;
		//	}
		//}
	}

	return map;
}

std::vector<std::vector<int>> Generator::CreateHall(Node* root, std::vector<std::vector<int>> curMap)
{	
	//std::vector<std::vector<int>> mapOutput;
	//for (int i = 0; i < 30; i++)
	//{
	//	std::vector<int> row;
	//	//row.reserve(32);
	//	for (int y = 0; y < 30; y++)
	//	{
	//		row.push_back(0);
	//	}
	//	mapOutput.push_back(row);
	//}

	if (root->A != NULL && root->B != NULL)
	{

		//sstd::cout << "Pair1: " << root->A->row << ", " << root->A->column << " ::: " << root->B->row << ", " << root->B->column << std::endl;

		int nodeAHeight = root->A->height;
		int nodeBHeight = root->B->height;
		int nodeAWidth = root->A->width;
		int nodeBWidth = root->B->width;

		//int AHalf1 = nodeAHeight / 2;
		//int AHalf2 = nodeAWidth / 2;
		//int BHalf1 = nodeBHeight / 2;
		//int BHalf2 = nodeBWidth / 2;

		//int ranX1 = rand() % (nodeAHeight - AHalf1) + AHalf1;
		//int ranX2 = rand() % (nodeBHeight - BHalf1) + BHalf1;
		//int ranY1 = rand() % (nodeAWidth - AHalf2) + AHalf2;
		//int ranY2 = rand() % (nodeBWidth - BHalf2) + BHalf2;

		//for (int r = root->A->row + 1; r < (root->A->row + ranX1); r++)
		//{
		//	for (int c = root->A->column + 1; c < (root->A->column + ranY1); c++)
		//	{
		//		//std::cout << "Adding tile thing at R: " << r << " , C: " << c << std::endl;
		//		curMap[r][c] = 0;
		//	}
		//}

		//for (int r = root->B->row + 1; r < (root->B->row + ranX2); r++)
		//{
		//	for (int c = root->B->column + 1; c < (root->B->column + ranY2); c++)
		//	{
		//		//std::cout << "Adding tile thing at R: " << r << " , C: " << c << std::endl;
		//		curMap[r][c] = 0;
		//	}
		//}

		int Room1XCenter = root->A->row + (root->A->height / 2);
		int Room1YCenter = root->A->column + (root->A->width / 2) + 1;

		//curMap[Room1YCenter][Room1XCenter] = 1;
		int Room2XCenter = root->B->row + (root->B->height / 2);
		int Room2YCenter = root->B->column + (root->B->width / 2) + 1;
		//curMap[Room2YCenter][Room2XCenter] = 1;
#
		int distance = sqrt(pow(Room2XCenter - Room1XCenter, 2) +
			pow(Room2YCenter - Room1YCenter, 2) * 1.0);

		//std::cout << "Distance: " << distance << std::endl;

		//std::cout << "Room1 Center: " << Room1XCenter << ", " << Room1YCenter << " : Room2 Center: " << Room2XCenter << ", " << Room2YCenter << std::endl;

		if (Room2XCenter == Room1XCenter)
		{
			if (Room2YCenter > Room1YCenter)
			{
				for (int i = 0; i < distance; i++)
				{
					curMap[Room1XCenter][Room1YCenter + i] = 0;
				}
			}
			else
			{
				for (int i = 0; i < distance; i++)
				{
					curMap[Room1XCenter][Room1YCenter - i] = 0;
				}
			}
		}
		else
		{
			if (Room2XCenter > Room1XCenter)
			{
				for (int i = 0; i < distance; i++)
				{
					curMap[Room1XCenter + i][Room1YCenter] = 0;
				}
			}
			else
			{
				for (int i = 0; i < distance; i++)
				{
					curMap[Room1XCenter - i][Room1YCenter] = 0;
				}
			}
		}
	}

		if (root->A != NULL)
		{
			curMap = CreateHall(root->A, curMap);
		}
		if (root->B != NULL)
		{
			curMap = CreateHall(root->B, curMap);
		}


	return curMap;
}

std::vector<std::vector<int>> Generator::GenerateAgent(int xVal, int yVal, int switchChance, int roomChance, int iterations)
{
	std::vector<std::vector<int>> mapOutput;
	for (int i = 0; i < xVal; i++)
	{
		std::vector<int> row;
		//row.reserve(32);
		for (int y = 0; y < yVal; y++)
		{
			row.push_back(0);
		}
		mapOutput.push_back(row);
	}

	int ran1 = rand() % (xVal - 1);
	int ran2 = rand() % (yVal - 1);
	int randPoint[2];
	randPoint[0] = ran1;
	//std::cout << "Rand point 0 = " << randPoint[0] << std::endl;
	randPoint[1] = ran2;

	int point[2];
	point[0] = randPoint[0];
	point[1] = randPoint[1];

	int direction = rand() % 3;

	for (int i = 0; i < iterations; i++)
	{
		//std::cout << "Current point: " << point[0] << ", " << point[1] << std::endl;

		if ((rand() % 100 + 1) <= switchChance)
		{
			int pastDir = direction;
			while (direction == pastDir)
			{
				direction = rand() % 3;
			}
		}

		if ((rand() % 100 + 1) <= roomChance)
		{
			//std::cout << "Placing room" << std::endl;
			// Do Room Code;
			int randXSize = rand() % 6 + 2;
			int randYSize = rand() % 6 + 2; 
			//std::cout << "Room Size = " << randXSize << ", " << randYSize << std::endl;
			if (randXSize % 2 == 0)
			{
				for (int x = 0 - (randXSize / 2); x < (randXSize / 2); x++)
				{
					if (randYSize % 2 == 0)
					{
						for (int y = 0 - (randYSize / 2); y < (randYSize / 2); y++)
						{
							if (point[0] + x < xVal && point[0] + x >= 0 && point[1] + y < yVal && point[1] + y >= 0)
							{
								int p1 = point[0] + x;
								int p2 = point[1] + y;
								//std::cout << "Trying to place at: " << p1 << ", " << p2 << std::endl;
								mapOutput[point[0] + x][point[1] + y] = 1;
							}

						}
					}
					else
					{
						for (int y = 0 - (randYSize / 2); y < ((randYSize / 2) + 1); y++)
						{
							if (point[0] + x < xVal && point[0] + x >= 0 && point[1] + y < yVal && point[1] + y >= 0)
							{
								int p1 = point[0] + x;
								int p2 = point[1] + y;
							//	std::cout << "Trying to place at: " << p1 << ", " << p2 << std::endl;
								mapOutput[point[0] + x][point[1] + y] = 1;
							}
						}
					}
				}
			}
			else
			{
				for (int x = 0 - (randXSize / 2); x < ((randXSize / 2) + 1); x++)
				{
					if (randYSize % 2 == 0)
					{
						for (int y = 0 - (randYSize / 2); y < (randYSize / 2); y++)
						{
							if (point[0] + x < xVal && point[0] + x >= 0 && point[1] + y < yVal && point[1] + y >= 0)
							{
								int p1 = point[0] + x;
								int p2 = point[1] + y;
								//std::cout << "Trying to place at: " << p1 << ", " << p2 << std::endl;
								mapOutput[point[0] + x][point[1] + y] = 1;
							}
						}
					}
					else
					{
						for (int y = 0 - (randYSize / 2); y < ((randYSize / 2) + 1); y++)
						{
							if (point[0] + x < xVal && point[0] + x >= 0 && point[1] + y < yVal && point[1] + y >= 0)
							{
								int p1 = point[0] + x;
								int p2 = point[1] + y;
							//	std::cout << "Trying to place at: " << p1 << ", " << p2 << std::endl;
								mapOutput[point[0] + x][point[1] + y] = 1;
							}
						}
					}
				}
			}
		}

		switch (direction)
		{
		//North
		case 0:

			if (point[1] != 0)
			{
				mapOutput[point[0]][point[1] - 1] = 3;
				point[1]--;
				break;
			}
			else
			{
				i--;
				break;
			}

		//East
		case 1:

			if (point[0] != (xVal - 1))
			{
				mapOutput[point[0] + 1][point[1]] = 3;
				point[0]++;
				break;
			}
			else
			{
				i--;
				break;
			}

		//South
		case 2:

			if (point[1] != (yVal - 1))
			{
				mapOutput[point[0]][point[1] + 1] = 3;
				point[1]++;
			}
			else
			{
				i--;
				break;
			}

		//West
		case 3:

			if (point[0] != 0)
			{
				mapOutput[point[0] - 1][point[1]] = 3;
				point[0]--;
			}
			else
			{
				i--;
				break;
			}
		}
	}

	return mapOutput;
}

static const float pi = 3.141592654f;

std::vector<int> Generator::getRandomPoint(int radius)
{
	float t = 2 * pi * ((float)rand() / RAND_MAX);
	//std::cout << "t = " << t << std::endl;
	float u = ((float)rand() / RAND_MAX) + ((float)rand() / RAND_MAX);
	//std::cout << "u = " << u << std::endl;
	float r = NULL;
	if (u > 1)
	{
		r = 2 - u;
	}
	else
	{
		r = u;
	}

	//std::cout << "r = " << r << std::endl;

	float point[2];
	point[0] = radius * r * cos(t);
	point[1] = radius * r * sin(t);

	/*if (point[0] == 0.0f && point[1] == 0.0f)
	{
		std::vector<int> tempPoint;
		tempPoint = getRandomPoint(radius);
		point[0] = tempPoint[0];
		point[1] = tempPoint[1];
	}*/

	//std::cout << "In RAN 1: " << (float)point[0] << std::endl;
	//std::cout << "In RAN 2: " << (float)point[1] << std::endl;

	std::vector<int> points;
	points.push_back(point[0] + radius + 30);
	points.push_back(point[1] + radius + 30);


	return points;
}

std::vector<std::vector<int>> Generator::GenerateConstraint(int xSize, int ySize, bool stepActive, int noIter, int roomMax, int roomMin, int noRooms, int radius)
{

	std::vector<std::vector<int>> mapOutput;
	for (int i = 0; i < xSize; i++)
	{
		std::vector<int> row;
		//row.reserve(32);
		for (int y = 0; y < ySize; y++)
		{
			row.push_back(1);
		}
		mapOutput.push_back(row);
	}

	std::vector<std::vector<int>> rooms;

	if (!stepActive || bounceStep == 0)
	{
		for (int i = 0; i < noRooms; i++)
		{
			std::vector<int> ranPoint;
			ranPoint = getRandomPoint(radius);
			//std::cout << "ranPoint 1: " << (float)ranPoint[0] << std::endl;
			//std::cout << "ranPoint 2: " << (float)ranPoint[1] << std::endl;
			int ranXSize = rand() % roomMax + 2;
			int ranYSize = rand() % roomMax + 2;

			std::cout << "Trying to change point at: " << ranPoint[0] + ranXSize << ", " << ranPoint[1] + ranYSize << std::endl;

			std::vector<int> room;

			room.push_back(ranPoint[0]);
			room.push_back(ranPoint[1]);
			room.push_back(ranXSize);
			room.push_back(ranYSize);

			rooms.push_back(room);

			for (int x = 0; x < ranXSize; x++)
			{
				for (int y = 0; y < ranYSize; y++)
				{
					//std::cout << "Trying to change point at: " << ranPoint[0] + ranXSize << ", " << ranPoint[1] + ranYSize << std::endl;
					//mapOutput[ranPoint[0] + x][ranPoint[1] + y] = 0;
				}
			}
		}
	}
	else
	{
		rooms = stepRooms;
	}


	for (int q = 0; q < noIter; q++)
	{
		for (int i = 0; i < rooms.size(); i++)
		{
			for (int r = 0; r < rooms.size(); r++)
			{
				if (r != i)
				{
					int roomXVal = rooms[i][0];
					int roomYVal = rooms[i][1];
					int roomXSize = rooms[i][2];
					int roomYSize = rooms[i][3];

					int room2XVal = rooms[r][0];
					int room2YVal = rooms[r][1];
					int room2XSize = rooms[r][2];
					int room2YSize = rooms[r][3];

					for (int x = -1; x < roomXSize + 1; x++)
					{
						for (int y = -1; y < roomYSize + 1; y++)
						{
							for (int g = -1; g < room2XSize + 1; g++)
							{
								for (int h = -1; h < room2YSize + 1; h++)
								{
									/*if (roomXVal + x > rooms[r][0] && roomYVal + y > rooms[r][1]
										&& roomXVal + x <= rooms[r][0] + g && roomYVal + y <= rooms[r][1] + h)
									{*/

										if(roomXVal + x == room2XVal + g && roomYVal + y == room2YVal + h)
										{
										if (roomXVal > room2XVal)
										{
											rooms[i][0] += 1;
										}
										else
										{
											rooms[i][0] -= 1;
										}

										if (roomYVal > room2YVal)
										{
											rooms[i][1] += 1;
										}
										else
										{
											rooms[i][1] -= 1;
										}
										x = roomXSize;
										y = roomYSize;
										g = room2XSize;
										h = room2YSize;
									}
								}
							}

							//if (roomXVal >= rooms[r][0] && roomXVal <= rooms[r][0] + rooms[r][2]
							//	|| roomXVal + roomXSize >= rooms[r][0] && roomXVal + roomXSize <= rooms[r][0] + rooms[r][2])
							//{
							//	if (roomYVal >= rooms[r][1] && roomYVal <= rooms[r][1] + rooms[r][3]
							//		|| roomYVal + roomYSize >= rooms[r][1] && roomYVal + roomYSize <= rooms[r][1] + rooms[r][3])
							//	{
							//	/*	rooms[i][0] += 1;
							//		rooms[i][1] += 1;*/

							//		if (roomXVal > 50)
							//		{
							//			rooms[i][0] += 1;
							//		}
							//		else
							//		{
							//			rooms[i][0] -= 1;
							//		}

							//		if (roomYVal > 50)
							//		{
							//			rooms[i][1] += 1;
							//		}
							//		else
							//		{
							//			rooms[i][1] -= 1;
							//		}
							//	}
							//}
						}
					}
				}
			}
		}
	}

	//std::cout << "Made it to splitting" << std::endl;

	for (int i = 0; i < rooms.size(); i++)
	{
		for (int x = 0; x < rooms[i][2]; x++)
		{
			for (int y = 0; y < rooms[i][3]; y++)
			{
			//	std::cout << "Point 1: " << rooms[i][0] + x << std::endl;
			//	std::cout << "Point 2: " << rooms[i][1] + y << std::endl;
				mapOutput[rooms[i][0] + x][rooms[i][1] + y] = 0;
			}
		}
	}

	stepRooms = rooms;
	bounceStep++;

	return mapOutput;
}

std::vector<std::vector<int>> Generator::ConstraintGraph(int xInput, int yInput)
{
	std::vector<std::vector<int>> mapOutput;
	for (int i = 0; i < xInput; i++)
	{
		std::vector<int> row;
		//row.reserve(32);
		for (int y = 0; y < yInput; y++)
		{
			row.push_back(1);
		}
		mapOutput.push_back(row);
	}

	std::vector<double> coords;

	for (int i = 0; i < stepRooms.size(); i++)
	{
		coords.push_back(stepRooms[i][0]);
		coords.push_back(stepRooms[i][1]);
	}

	std::cout << "before d" << std::endl;

	delaunator::Delaunator d(coords);

	for (int i = 0; i < stepRooms.size(); i++)
	{
		for (int x = 0; x < stepRooms[i][2]; x++)
		{
			for (int y = 0; y < stepRooms[i][3]; y++)
			{
				//	std::cout << "Point 1: " << rooms[i][0] + x << std::endl;
				//	std::cout << "Point 2: " << rooms[i][1] + y << std::endl;
				mapOutput[stepRooms[i][0] + x][stepRooms[i][1] + y] = 0;
			}
		}
	}

	return mapOutput;

}

std::vector<std::vector<int>> Generator::ConstraintCorridors(int xInput, int yInput, int bounceDist)
{
	std::vector<std::vector<int>> mapOutput;
	for (int i = 0; i < xInput; i++)
	{
		std::vector<int> row;
		//row.reserve(32);
		for (int y = 0; y < yInput; y++)
		{
			row.push_back(1);
		}
		mapOutput.push_back(row);
	}

	for (int i = 0; i < stepRooms.size(); i++)
	{
		for (int x = 0; x < stepRooms[i][2]; x++)
		{
			for (int y = 0; y < stepRooms[i][3]; y++)
			{
				//	std::cout << "Point 1: " << rooms[i][0] + x << std::endl;
				//	std::cout << "Point 2: " << rooms[i][1] + y << std::endl;
				mapOutput[stepRooms[i][0] + x][stepRooms[i][1] + y] = 0;
			}
		}
	}

	for (int i = 0; i < stepRooms.size(); i++)
	{
		for (int r = 0; r < stepRooms.size(); r++)
		{
			if (i != r)
			{
				int x1Cent = stepRooms[i][0] + (0.5 * stepRooms[i][2]);
				int y1Cent = stepRooms[i][1] + (0.5 * stepRooms[i][3]);
				int x2Cent = stepRooms[r][0] + (0.5 * stepRooms[r][2]);
				int y2Cent = stepRooms[r][1] + (0.5 * stepRooms[r][3]);

				int distance = sqrt(pow(x2Cent - x1Cent, 2) +
					pow(y2Cent - y1Cent, 2) * 1.0);

				if (distance < bounceDist)
				{
					bool pathing = true;
					int ranDir = rand() % 1;
					int totalX = 0;
					int totalY = 0;
					do {
						if (x2Cent > x1Cent)
						{
							//Bottom Right
							if (y2Cent > y1Cent)
							{
								if (ranDir == 0)
								{
									if (x1Cent + totalX != x2Cent)
									{
										mapOutput[x1Cent + totalX][y1Cent + totalY] = 0;
										totalX++;
									}
									else
									{
										mapOutput[x1Cent + totalX][y1Cent + totalY] = 0;
										totalY++;
									}
								}
								else
								{
									if (y1Cent + totalY != y2Cent)
									{
										mapOutput[x1Cent + totalX][y1Cent + totalY] = 0;
										totalY++;
									}
									else
									{
										mapOutput[x1Cent + totalX][y1Cent + totalY] = 0;
										totalX++;
									}
								}

								if (x1Cent + totalX == x2Cent && y1Cent + totalY == y2Cent)
								{
									pathing = false;
								}
							}
							else
							{
								//Top Right
								if (ranDir == 0)
								{
									if (x1Cent + totalX != x2Cent)
									{
										mapOutput[x1Cent + totalX][y1Cent - totalY] = 0;
										totalX++;
									}
									else
									{
										mapOutput[x1Cent + totalX][y1Cent - totalY] = 0;
										totalY++;
									}
								}
								else
								{
									if (y1Cent - totalY != y2Cent)
									{
										mapOutput[x1Cent + totalX][y1Cent - totalY] = 0;
										totalY++;
									}
									else
									{
										mapOutput[x1Cent + totalX][y1Cent - totalY] = 0;
										totalX++;
									}
								}

								if (x1Cent + totalX == x2Cent && y1Cent - totalY == y2Cent)
								{
									pathing = false;
								}
							}
						}
						else
						{
							//Bottom Left
							if (y2Cent > y1Cent)
							{
								if (ranDir == 0)
								{
									if (x1Cent - totalX != x2Cent)
									{
										mapOutput[x1Cent - totalX][y1Cent + totalY] = 0;
										totalX++;
									}
									else
									{
										mapOutput[x1Cent - totalX][y1Cent + totalY] = 0;
										totalY++;
									}
								}
								else
								{
									if (y1Cent + totalY != y2Cent)
									{
										mapOutput[x1Cent - totalX][y1Cent + totalY] = 0;
										totalY++;
									}
									else
									{
										mapOutput[x1Cent - totalX][y1Cent + totalY] = 0;
										totalX++;
									}
								}

								if (x1Cent - totalX == x2Cent && y1Cent + totalY == y2Cent)
								{
									pathing = false;
								}
							}
							else
							{
								//Top Left
								if (ranDir == 0)
								{
									if (x1Cent - totalX != x2Cent)
									{
										mapOutput[x1Cent - totalX][y1Cent - totalY] = 0;
										totalX++;
									}
									else
									{
										mapOutput[x1Cent - totalX][y1Cent - totalY] = 0;
										totalY++;
									}
								}
								else
								{
									if (y1Cent - totalY != y2Cent)
									{
										mapOutput[x1Cent - totalX][y1Cent - totalY] = 0;
										totalY++;
									}
									else
									{
										mapOutput[x1Cent - totalX][y1Cent - totalY] = 0;
										totalX++;
									}
								}

								if (x1Cent - totalX == x2Cent && y1Cent - totalY == y2Cent)
								{
									pathing = false;
								}
							}
						}

						} while (pathing);
					}
				}
			}
		}

		return mapOutput;
	}

	std::vector<std::vector<int>> Generator::FindEndpoint(std::vector<std::vector<int>> input)
	{
		int endpointX = 0;
		int endpointY = 0;

		//std::cout << "size =  " << input.size() << std::endl;

		int dis = 9999;
 
		for (int i = 0; i < input.size(); i++)
		{
			for (int r = 0; r < input.size(); r++)
			{
				if (input[i][r] == 0)
				{

					int distance = sqrt(pow(input.size() - i, 2) +
						pow(input.size() - r, 2) * 1.0);

					//std::cout << "calc distance = " << distance << std::endl;
					//std::cout << "dis = " << dis << std::endl;

					if (distance < dis)
					{
						endpointX = i;
						endpointY = r;
						dis = distance;
					}
				}
			}
		}

		input[endpointX][endpointY] = 4;
		std::cout << "Changing to key: " << endpointX << " , " << endpointY << std::endl;

		return input;
	}

	std::vector<std::vector<int>> Generator::ChangeToBlack(std::vector<std::vector<int>> input)
	{

		std::vector<std::vector<int>> tempMap;
		tempMap = input;

		for (int w = 0; w < input.size(); w++)
		{
			for (int b = 0; b < input.size(); b++)
			{
				int count = 0;
				bool touching = false;
				for (int i = -1; i < 2; i++) {
					for (int j = -1; j < 2; j++) {
						int neighbour_x = w + i;
						int neighbour_y = b + j;

						if (i == 0 && j == 0)
						{
							//nothing
						}
						else if (neighbour_x < 0 || neighbour_y < 0 || neighbour_x >= input.size() || neighbour_y >= input.size())
						{
							//count += 1;
						}
						else if (input[neighbour_x][neighbour_y] == 0)
						{
							touching = true;
						}
					}
				}

				if (touching == false)
				{
					tempMap[w][b] = 8;
				}
			}
		}

		for (int i = 0; i < input.size(); i++)
		{
			for (int y = 0; y < input.size(); y++)
			{
				if (tempMap[i][y] == 8)
				{
					input[i][y] = 8;
				}
			}
		}

		return input;
	}