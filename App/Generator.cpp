#include "Generator.h"
#include <random>

sf::Image Generator::GenerateDungeon(int caMap[], int iterations, int type)
{
	//pixels.create(xSize, ySize, sf::Color::Black);

	//Grid map = new Grid(xSize, ySize);
	Grid *map = new Grid(xSize, ySize);
	//int *rd = map->GetRandomPoint();

	if (type == 0)
	{
		std::random_device random;
		std::mt19937 gen(random());
		std::uniform_int_distribution<> w(0, map->Width), h(0, map->Height);
		int randPoint[2];
		randPoint[0] = w(gen);
		std::cout << "Rand point 0 = " << randPoint[0] << std::endl;
		randPoint[1] = h(gen);
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
			int direction = dir(gen);
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

std::vector<std::vector<int>> Generator::GenerateMapTiles(int x, int y, int AlivePercent, int BirthNum, int iterations, int DeathLimit, int type)
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
			if(((double)rand() / RAND_MAX) < cutOff)
			{
				row.push_back(1);
			}
			else
			{
				row.push_back(0);
			}
		}
		vecMap.push_back(row);
	}

	if (type == 0)
	{
		std::random_device random;
		std::mt19937 gen(random());
		std::uniform_int_distribution<> w(0, map->Width), h(0, map->Height);
		int randPoint[2];
		randPoint[0] = w(gen);
		std::cout << "Rand point 0 = " << randPoint[0] << std::endl;
		randPoint[1] = h(gen);
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
			int direction = dir(gen);
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

		map->InitRandom(aliveChance);

		//Grid* newMap = new Grid(xSize, ySize);

	//	std::cout << "Size of vector before = " << vecMap.size() << std::endl;
		for (int i = 0; i < iter; i++)
		{
			//std::cout << "Doing iteration!" << std::endl;
			//std::cout << "map test Val = " << map->GetTestVal() << std::endl;
			map = CAIteration(map, vecMap, deathLimit, birthNumber, x, y);
		}
		//std::cout << "map test Val = " << map->GetTestVal() << std::endl;
		for (int i = 0; i < x; i++)
		{
			for (int r = 0; r < y; r++)
			{
				if (map->GetPoint(i, r))
				{
				//	std::cout << "Trying to make 1" << std::endl;
					vecMap[i][r] = 1;
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

 std::vector<std::vector<int>> Generator::GenerateBSP(int depthMax, int SizeInt, int minHor, int maxHor, int minVer, int maxVer)
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
			row.push_back(0);
		}
		mapOutput.push_back(row);
	}
	std::random_device random;
	std::mt19937 gen(random());
	std::uniform_int_distribution<int> r(0, 1);

	Node* root = new Node();

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
	if (depth < depthMax)
	{
		Split(root, 0, depthMax, SizeInt, minHorMod, maxHorMod, minVerMod, maxVerMod);
	}

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

void Generator::Split(Node* node, int depth, int maxDepth, int SizeInt, float minHor, float maxHor, float minVer, float maxVer)
{

	std::random_device random;
	std::mt19937 gen(random());
	std::uniform_int_distribution<int> r(0, 1);

	node->A = new Node();
	node->B = new Node();

	if (r(gen) == 0)
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

	if (depth < maxDepth) {
		this->Split(node->A, (depth + 1), maxDepth, SizeInt, minHor, maxHor, minVer, maxVer);
		this->Split(node->B, (depth + 1), maxDepth, SizeInt, minHor, maxHor, minVer, maxVer);
	}
	else
	{
		// Otherwise, add the two nodes to the list of nodes to create rooms for.
		rooms.push_back(node->A);
		rooms.push_back(node->B);
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

		//std::cout << "Adding room!" << std::endl;
		for (int r = node->row + 1; r < (node->row + node->height); r++)
		{
			for (int c = node->column + 1; c < (node->column + node->width); c++)
			{
				//std::cout << "Adding tile thing at R: " << r << " , C: " << c << std::endl;

				map[r][c] = 3;
			}
		}
	}

	//for (int i = 0; i < rooms.size(); i++)
	//{
	//	Node* node = rooms[i];
	//	int xCenter = node->row + (node->height / 2);
	//	int yCenter = node->column + (node->width / 2);

	//	//map[xCenter][yCenter] = 3;
	//	std::cout << "XCenter " << xCenter << " , " << "YCenter " << yCenter << std::endl;
	//	Node* closestNode;
	//	int closestDist = 99999999;
	//	for (int s = 0; s < rooms.size(); s++)
	//	{
	//		Node* tempNode = rooms[s];
	//		int tempX = tempNode->row + (tempNode->width / 2);
	//		int tempY = tempNode->column + (tempNode->height / 2);

	//		//std::cout << "XTempCenter " << tempX << " , " << "YTempCenter " << tempX << std::endl;

	//		int distance = sqrt(pow(tempX - xCenter, 2) +
	//			pow(tempY - yCenter, 2) * 1.0);

	//		//std::cout << "Distance = " << distance << std::endl;

	//		if (distance < closestDist && distance != 0)
	//		{
	//			closestDist = distance;
	//			closestNode = tempNode;
	//		}
	//	}
	//}

		//std::cout << "Distance: " << closestDist << std::endl;

		//for (int i = 0; i < rooms.size(); i+=2)
		//{
		//	Node* room1 = rooms[i];
		//	Node* room2 = rooms[i + 1];

		//	int Room1XCenter = room1->column + (room1->width / 2);
		//	int Room1YCenter = room1->row + (room1->height / 2);

		//	int Room2XCenter = room2->column + (room2->width / 2);
		//	int Room2YCenter = room2->row + (room2->height / 2);

		//	//std::cout << "Pairs of rooms: 1 " << Room1XCenter << ", " << Room1YCenter << " :::2  " << Room2XCenter << ", " << Room2YCenter << std::endl;


		//}


	//	int xOtherCenter = closestNode->column + (closestNode->width / 2);
	//	int yOtherCenter = closestNode->row + (closestNode->height / 2);

	//	std::cout << "Distance2: " << closestDist << std::endl;
	//	//Hor
	//		if (xOtherCenter > xCenter)
	//		{
	//			int count = 0;
	//			std::cout << "Distance3: " << closestDist << std::endl;
	//			while (map[xCenter + (node->width / 2) + count][yCenter] == 0)
	//			{
	//				//count++;
	//				std::cout << "Trying to place: x+: " << (xCenter + (node->width / 2) + count) << std::endl;
	//				if (xCenter + (node->width / 2) + count >= 29 || xCenter + (node->width / 2) + count <= 0)
	//				{
	//					std::cout << "Danger" << std::endl;
	//					break;
	//				}
	//				std::cout << "NotDanger" << std::endl;
	//				//std::cout << "Trying to place: " << (xCenter + (node->width / 2) + count) << std::endl;
	//				count++;
	//				map[xCenter + (node->width / 2) + count][yCenter] = 2;
	//				//count++;
	//			}
	//		}
	//		else if (xOtherCenter < xCenter)
	//		{
	//			int count = 0;
	//			std::cout << "Distance4: " << closestDist << std::endl;
	//			while (map[xCenter + (node->width / 2) + count][yCenter] == 0)
	//			{
	//				//count--;
	//				std::cout << "Trying to place: x-: " << (xCenter + (node->width / 2) + count) << std::endl;
	//				if (xCenter + (node->width / 2) + count >= 29 || xCenter + (node->width / 2) + count <= 0)
	//				{
	//					std::cout << "Danger" << std::endl;
	//					break;
	//				}
	//				count--;
	//				//std::cout << "Trying to place: " << (xCenter + (node->width / 2) + count) << std::endl;
	//				map[xCenter + (node->width / 2) + count][yCenter] = 2;
	//			//	count--;
	//			}
	//		}
	//		else if (yOtherCenter > yCenter)
	//		{
	//			int count = 0;
	//			std::cout << "Distance5: " << closestDist << std::endl;
	//			while (map[xCenter][yCenter + (node->height / 2) + count] == 0)
	//			{
	//				//count++;
	//				std::cout << "Trying to place: y+: " << (yCenter + (node->width / 2) + count) << std::endl;
	//				if (yCenter + (node->height / 2) + count >= 29 || yCenter + (node->height / 2) + count <= 0)
	//				{
	//					std::cout << "Danger" << std::endl;
	//					break;
	//				}
	//				count++;
	//				//std::cout << "Trying to place: " << (xCenter + (node->width / 2) + count) << std::endl;
	//				map[xCenter][yCenter + (node->height / 2) + count] = 2;
	//				//count++;
	//			}
	//		}
	//		else if (yOtherCenter < yCenter)
	//		{
	//			int count = 0;
	//			std::cout << "Distance6: " << closestDist << std::endl;
	//			while (map[xCenter][yCenter + (node->height / 2) + count] == 0)
	//			{
	//				//count--;
	//				std::cout << "Trying to place: y-: " << (yCenter + (node->width / 2) + count) << std::endl;
	//				if (yCenter + (node->height / 2) + count >= 29 || yCenter + (node->height / 2) + count <= 0)
	//				{
	//					std::cout << "Danger" << std::endl;
	//					break;
	//				}
	//				count--;
	//			//std::cout << "Trying to place: " << (xCenter + (node->width / 2) + count) << std::endl;
	//				map[xCenter][yCenter + (node->height / 2) + count] = 2;
	//				//count--;
	//			}
	//	}
	//}

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

	if (root->A != NULL || root->B != NULL)
	{
		if (root->A != NULL)
		{
			curMap = CreateHall(root->A, curMap);
		}
		if (root->B != NULL)
		{
			curMap = CreateHall(root->B, curMap);
		}

		//std::cout << "Pair1: " << root->A->row << ", " << root->A->column << " ::: " << root->B->row << ", " << root->B->column << std::endl;

		int Room1XCenter = root->A->column + (root->A->width / 2);
		int Room1YCenter = root->A->row + (root->A->height / 2);

		int Room2XCenter = root->B->column + (root->B->width / 2);
		int Room2YCenter = root->B->row + (root->B->height / 2);
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
					curMap[Room1XCenter][Room1YCenter + i] = 1;
				}
			}
			else
			{
				for (int i = 0; i < distance; i++)
				{
					curMap[Room1XCenter][Room1YCenter - i] = 1;
				}
			}
		}
		else
		{
			if (Room2XCenter > Room1XCenter)
			{
				for (int i = 0; i < distance; i++)
				{
					curMap[Room1XCenter + i][Room1YCenter] = 1;
				}
			}
			else
			{
				for (int i = 0; i < distance; i++)
				{
					curMap[Room1XCenter - i][Room1YCenter] = 1;
				}
			}
		}

	}

	return curMap;
}