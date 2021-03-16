
#pragma once
#include <SFML/Graphics.hpp>
#include "TileMap.h"
#include <chrono>


class Player {
protected:

	sf::RectangleShape shape;

	int speed = 1;
	int tileX;
	int tileY;

public:
	Player(int speedIn) { speed = speedIn; };
	virtual ~Player() = default;
	//sf::Sprite sprite;

	virtual void Update(std::vector<std::vector<int>> map, int Size);
	virtual void Load(int xPos, int yPos, bool random, std::vector<std::vector<int>> map);
	sf::RectangleShape GetSprite();
	sf::Vector2f GetPos();
	//virtual void Render() {};
	//virtual void Load();

};