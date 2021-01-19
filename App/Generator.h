#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "Grid.h"

struct Node {
	int row, column;
	int width, height;

	Node* A;
	Node* B;
};

class Generator {
protected:
	sf::String method;
	//std::vector<std::vector<int>> dungeon;
	int xSize;
	int ySize;

	sf::Image pixels;

	std::vector<Node*> rooms;

public:
	Generator(sf::String methodType, int x, int y) { xSize = x, ySize = y, method = methodType;};
	virtual ~Generator() = default;

	virtual sf::Image GenerateDungeon(int iterations);
	virtual sf::Image GenerateBSP();
	virtual void Split(Node* node, int depth, int maxDepth);
	sf::Image GenerateImageBSP();
	//virtual void Render() {};
	//virtual void Load();
};