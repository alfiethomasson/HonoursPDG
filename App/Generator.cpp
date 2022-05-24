#include "Generator.h"
#include <random>
#include <math.h> 

sf::Image Generator::GenerateDungeon(int caMap[], int iterations, int type)
{
	Grid *map = new Grid(xSize, ySize);

	if (type == 0) // DrunkardWalk
	{

		int ran1 = rand() % map->Width;
		int ran2 = rand() % map->Height;
		int randPoint[2];
		randPoint[0] = ran1;
		randPoint[1] = ran2;
		int point[2];
		point[0] = randPoint[0];
		point[1] = randPoint[1];

		std::uniform_int_distribution<> dir(0, 3);

		for (int i = 0; i < iterations; i++)
		{
			int direction = rand() % 3;
			switch (direction)
			{
				//North
			case 0:
				//std::cout << "North" << endl;
				if (point[1] != 0)
				{
					unsigned int point0 = point[0];
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
	else // Cellular Automata 
	{
		//Outdated, replaced below.
		float aliveChance = 0.42f;
		int starvationLimit = 0;
		int overpopLimit = 0;
		int birthNumber = 4;
		int iter = 2;

		int deathLimit = 3;

		map->InitRandom(aliveChance);

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

void Generator::Reset(int x, int y, int alivePercent) //Resets algorithms
{
	float aliveChance = (float)alivePercent / 100;
	stepMap = new Grid(x, y);
	stepMap->InitRandom(aliveChance);
	stepRoot = new Node();
	totalBSPIterations = 0;
	stepRooms.clear();
	bounceStep = 0;
}

//Drunkard Walk and Cellular Automata for updated tileset system
std::vector<std::vector<int>> Generator::GenerateMapTiles(int x, int y, int AlivePercent, int BirthNum, int iterations, int DeathLimit, int type, bool stepBool, int numberIterations)
{
	Grid* map = new Grid(x, y);

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

	if (type == 0) // Drunkard Walk
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
			int direction = rand() % 4;
			switch (direction)
			{
				//North
			case 0:
				//std::cout << "North" << endl;
				if (point[1] != 0)
				{
					//std::cout << point[0] << ", " << point[1] << endl;
					//map->FillPoint(point[0], point[1] - 1);
					vecMap[point[0]][point[1] - 1] = 0;
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
					vecMap[point[0] - 1][point[1]] = 0;
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
					vecMap[point[0]][point[1] + 1] = 0;
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
					vecMap[point[0] + 1][point[1]] = 0;
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
	else // Cellular Automata
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
			for (int i = 0; i < numberIterations; i++)
			{
				map = CAIteration(map, vecMap, deathLimit, birthNumber, x, y);
			}
			stepMap = map;
			for (int i = 0; i < x; i++)
			{
				for (int r = 0; r < y; r++)
				{
					if (map->GetPoint(i, r))
					{
						vecMap[i][r] = 0;
					}
				}
			}
		}


	return vecMap;
}

Grid* Generator::CAIteration(Grid* oldMap, std::vector<std::vector<int>> tileMap, int deathLimit, int birthNumber, int xVal, int yVal) //Cellular Automata step
{
	Grid* newMap = new Grid(xVal, yVal);
	newMap->SetTestVal(10);
	for (int x = 0; x < xVal; x++)
	{
		for (int y = 0; y < yVal; y++)
		{
			int neighbours = countAliveNeighbours(oldMap, x, y, xVal, yVal);

			if (oldMap->GetPoint(x, y))
			{
				if (neighbours < deathLimit)
				{
					newMap->EmptyPoint(x, y);
				}
				else
				{
					newMap->FillPoint(x, y);
				}
			}
			else
			{
				if (neighbours > birthNumber)
				{
					newMap->FillPoint(x, y);
				}
				else
				{
					newMap->EmptyPoint(x, y);
				}
			}
		}
	}

	return newMap;
}

 int Generator::countAliveNeighbours(Grid* map, int x, int y, int xVal, int yVal) { // Counts neighbours for CA
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

 // BSP Output
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

	std::vector<std::vector<int>> returnedMap = GenerateBSPOutput(mapOutput);

	return returnedMap;

}

 std::vector<std::vector<int>> Generator::AddCorridors(int SizeInt) // Adds corridors to BSP
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

 //BSP Iteration, splits nodes
void Generator::Split(Node* node, int depth, int maxDepth, int SizeInt, float minHor, float maxHor, float minVer, float maxVer, int totalIterations, bool doAll)
{
	if (depth == totalIterations || !doAll)
	{
		node->A = new Node();
		node->B = new Node();

		int split;
		int splitTemp = rand() % 1;
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

		node->A->parentSplit = split;
		node->B->parentSplit = split;

		if (split)
		{
			int min = (int)(minVer * node->height);
			int max = (int)(maxVer * node->height);
			int rowLine = ((rand() % (max - min)) + min);
			node->A->row = node->row;
			node->A->column = node->column;
			node->A->width = node->width;
			node->A->height = (((node->A->row + rowLine)) - node->A->row);

			node->B->row = (node->A->row + (rowLine));
			node->B->column = node->column;
			node->B->width = node->width;
			node->B->height = (node->height - node->A->height);
		}
		else
		{
			int min = (int)(minHor * node->width);
			int max = (int)(maxHor * node->width);
			int colLine = ((rand() % (max - min)) + min);
			node->A->row = node->row;
			node->A->column = node->column;
			node->A->width = (((node->A->column + colLine)) - node->A->column);
			node->A->height = node->height;

			node->B->row = node->row;
			node->B->column = (node->A->column + (colLine));
			node->B->width = (node->width - node->A->width);
			node->B->height = node->height;
		}
		rooms.push_back(node->A);
		rooms.push_back(node->B);
	}
	if(depth < totalIterations)
	{
		if (depth < maxDepth) {
			this->Split(node->A, (depth + 1), maxDepth, SizeInt, minHor, maxHor, minVer, maxVer, totalIterations, doAll);
			this->Split(node->B, (depth + 1), maxDepth, SizeInt, minHor, maxHor, minVer, maxVer, totalIterations, doAll);
		}
	}
}

sf::Image Generator::GenerateImageBSP() // Generates an image for BSP, currently outdated
{
	pixels.create(xSize, ySize, sf::Color::Black);

	for (int i = 0; i < rooms.size(); i++)
	{
		Node* node = rooms[i];
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

std::vector<std::vector<int>> Generator::GenerateBSPOutput(std::vector<std::vector<int>> map) //Turns BSP output into a nested vector which can be displayed
{
	for (int i = 0; i < rooms.size(); i++)
	{
		Node* node = rooms[i];

		int roomX = node->row + node->height;
		int roomY = node->column + node->width;


		std::cout << "Adding room!" << std::endl;
		for (int r = node->row + 1; r < (node->row + node->height); r++)
		{
			for (int c = node->column + 1; c < (node->column + node->width); c++)
			{
				map[r][c] = 0;
			}
		}
	}

	for (int r = 0; r < map.size(); r++)
	{
		map[map.size() - 1][r] = 1;
		map[r][map.size() - 1] = 1;
	}

	return map;

}

std::vector<std::vector<int>> Generator::BSPRandomRooms(std::vector<std::vector<int>> map) // Generates rooms for BSP
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

		for (int r = (node->row + halfX - randomX); r < (node->row + halfX + randomX); r++)
		{
			for (int c = (node->column + halfY - randomY); c < (node->column + halfY + randomY); c++)
			{
				map[r][c] = 0;
			}
		}

		std::cout << "Row & Height: " << node->row << ", " << node->height << std::endl;
		std::cout << "Column & Width: " << node->column << ", " << node->width << std::endl;

		std::cout << "Random X + Y: " << randomX << " , " << randomY << std::endl;

	}

	return map;
}

std::vector<std::vector<int>> Generator::CreateHall(Node* root, std::vector<std::vector<int>> curMap) // Creates corridors between rooms with BSP
{	

	if (root->A != NULL && root->B != NULL)
	{


		int nodeAHeight = root->A->height;
		int nodeBHeight = root->B->height;
		int nodeAWidth = root->A->width;
		int nodeBWidth = root->B->width;

		int Room1XCenter = root->A->row + (root->A->height / 2);
		int Room1YCenter = root->A->column + (root->A->width / 2) + 1;

		int Room2XCenter = root->B->row + (root->B->height / 2);
		int Room2YCenter = root->B->column + (root->B->width / 2) + 1;
#
		int distance = sqrt(pow(Room2XCenter - Room1XCenter, 2) +
			pow(Room2YCenter - Room1YCenter, 2) * 1.0);


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

std::vector<std::vector<int>> Generator::GenerateAgent(int xVal, int yVal, int switchChance, int roomChance, int iterations) //Agent method, currently outdated and done in main.cpp
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
	randPoint[1] = ran2;

	int point[2];
	point[0] = randPoint[0];
	point[1] = randPoint[1];

	int direction = rand() % 3;

	for (int i = 0; i < iterations; i++)
	{

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
			// Do Room Code;
			int randXSize = rand() % 6 + 2;
			int randYSize = rand() % 6 + 2; 
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

std::vector<int> Generator::getRandomPoint(int radius) // Gets random point in a cirucle, used for constraint
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

	float point[2];
	point[0] = radius * r * cos(t);
	point[1] = radius * r * sin(t);


	std::vector<int> points;
	points.push_back(point[0] + radius + 30);
	points.push_back(point[1] + radius + 30);


	return points;
}

std::vector<std::vector<int>> Generator::GenerateConstraint(int xSize, int ySize, bool stepActive, int noIter, int roomMax, int roomMin, int noRooms, int radius) // Constraint based generation
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
						}
					}
				}
			}
		}
	}

	for (int i = 0; i < rooms.size(); i++)
	{
		for (int x = 0; x < rooms[i][2]; x++)
		{
			for (int y = 0; y < rooms[i][3]; y++)
			{
				mapOutput[rooms[i][0] + x][rooms[i][1] + y] = 0;
			}
		}
	}

	stepRooms = rooms;
	bounceStep++;

	return mapOutput;
}

std::vector<std::vector<int>> Generator::ConstraintGraph(int xInput, int yInput) //Attempt at delunaey triangulation, outdated.
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

	//delaunator::Delaunator d(coords);

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

std::vector<std::vector<int>> Generator::ConstraintCorridors(int xInput, int yInput, int bounceDist) // Corridors for constraint based
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

	std::vector<std::vector<int>> Generator::FindEndpoint(std::vector<std::vector<int>> input) // Finds the end point of an algorithm, i.e the bottom right most accessible point of the map
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

		return input;
	}

	std::vector<std::vector<int>> Generator::ChangeToBlack(std::vector<std::vector<int>> input) // Changes non-wall tiles to black for visibility.
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