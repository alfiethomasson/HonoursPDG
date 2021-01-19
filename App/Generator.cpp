#include "Generator.h"

sf::Image Generator::GenerateDungeon(int iterations)
{
	pixels.create(xSize, ySize, sf::Color::Black);

	//Grid map = new Grid(xSize, ySize);
	Grid *map = new Grid(xSize, ySize);
	//int *rd = map->GetRandomPoint();
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

	return pixels;

//map->Print();
}

sf::Image Generator::GenerateBSP()
{
	Grid* map = new Grid(xSize, ySize);
	std::random_device random;
	std::mt19937 gen(random());
	std::uniform_int_distribution<int> r(0, 1);

	Node* root = new Node();

	root->row = 0;
	root->column = 0;
	root->width = xSize;
	root->height = ySize;

	int depth = 0;
	if (depth < 5)
	{
		Split(root, 0, 5);
	}

	sf::Image img = GenerateImageBSP();

	//int random = r(gen);
	//if (r(gen) == 0)
	//{
	//	std::uniform_int_distribution<int> w(xSize * 0.4, ySize * 0.6);

	//}
	//else
	//{

	//}
	return img;

}

void Generator::Split(Node* node, int depth, int maxDepth)
{
	std::random_device random;
	std::mt19937 gen(random());
	std::uniform_int_distribution<int> r(0, 1);

	node->A = new Node();
	node->B = new Node();

	if (r(gen) == 0)
	{
		int min = (int)(0.3 * node->height);
		int max = (int)(0.6 * node->height);
		std::cout << "Horizontal split" << std::endl;
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
		std::cout << "Vertical split" << std::endl;
		int min = (int)(0.3 * node->width);
		int max = (int)(0.6 * node->width);
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
		this->Split(node->A, (depth + 1), maxDepth);
		this->Split(node->B, (depth + 1), maxDepth);
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
		std::cout << "Got a room here: " << i << std::endl;
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