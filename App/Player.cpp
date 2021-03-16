#include "Player.h"

sf::Clock c;
float timer = 0.0f;

void Player::Update(std::vector<std::vector<int>> map, int Size)
{
	//c.restart();
	float t = c.restart().asSeconds();

//	std::cout << "Timer = " << timer << std::endl;
	timer += t;

	//PLAYER MOVEMENT
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) //Move Up
	{
		if (tileY != 0)
		{
			//std::cout << "Left" << std::endl;
			if (map[tileX][tileY - 1] != 1)
			{
				if (timer > 0.1f)
				{
				//	std::cout << "Up" << std::endl;
					tileY -= 1;
					timer = 0.0f;
				}
			}
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) //Move Down
	{
		if (tileY != map.size() - 1)
		{
			//std::cout << "Left" << std::endl;
			if (map[tileX][tileY + 1] != 1)
			{
				if (timer > 0.1f)
				{
				//	std::cout << "Down" << std::endl;
					tileY += 1;
					timer = 0.0f;
				}
			}
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) //Move Right
	{
		if (tileX != map.size() - 1)
		{
			//std::cout << "Left" << std::endl;
			if (map[tileX + 1][tileY] != 1)
			{
				if (timer > 0.1f)
				{
					//std::cout << "Right" << std::endl;
					tileX += 1;
					timer = 0.0f;
				}
			}

		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) //Move Left
	{
		if (tileX != 0)
		{
			//std::cout << "Left" << std::endl;
			if (map[tileX - 1][tileY] != 1)
			{
				if (timer > 0.1f)
				{
					//std::cout << "Left" << std::endl;
					tileX -= 1;
					timer = 0.0f;
				}
			}
		}
	}
	shape.setPosition(tileX * 32, tileY * 32);
}

void Player::Load(int xPos, int yPos, bool random, std::vector<std::vector<int>> map)
{
	sf::Texture playerTex;
	if (!playerTex.loadFromFile("D:/Github/HonoursPDG/Red.png"))
	{
	//	std::cout << "Failed to load player texture" << std::endl;
	}
	if (!random)
	{
		tileX = 0;
		tileY = 0;

		int tileXNum = 999;
		int tileYNum = 999;

		int dis = 9999;

		for (int i = 0; i < map.size(); i++)
		{
			for (int r = 0; r < map.size(); r++)
			{
				if (map[i][r] == 0)
				{

					int distance = sqrt(pow(0 - i, 2) +
						pow(0 - r, 2) * 1.0);

				//	std::cout << "calc distance = " << distance << std::endl; 
					//	std::cout << "dis = " << dis << std::endl;

					if (distance < dis)
					{
						tileXNum = i;
						tileYNum = r;
						dis = distance;
					}

					/*if (tileXNum > i)
					{
						if (tileYNum > r)
						{
							tileXNum = i;
							tileYNum = r;
						}
					}*/
				}
			}
		}

		tileX = tileXNum;
		tileY = tileYNum;

		std::cout << "tile x = " << tileXNum << std::endl;
		std::cout << "tile y = " << tileYNum << std::endl;

	}
	else
	{
		int ranX;
		int ranY;

		std::cout << "map size = " << map.size() << std::endl;

		do {
			ranX = rand() % map.size();
			ranY = rand() % map.size();
		} while (map[ranX][ranY] == 1);

		tileX = ranX;
		tileY = ranY;
	}

	sf::RectangleShape tempshape(sf::Vector2f(32, 32));
	shape = tempshape;
	shape.setFillColor(sf::Color::Red);
	shape.setPosition(tileX * 32, tileY * 32);
}

sf::RectangleShape Player::GetSprite()
{
	return shape;
}

sf::Vector2f Player::GetPos()
{
	return shape.getPosition();
}