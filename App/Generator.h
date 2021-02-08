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

	virtual sf::Image GenerateDungeon(int caMap[], int iterations, int type);
	std::vector<std::vector<int>> Generator::GenerateMapTiles(int x, int y, int AlivePercent, int BirthNum, int iterations, int DeathLimit, int type);
	Grid* CAIteration(Grid* oldMap, std::vector<std::vector<int>> tileMap, int deathNum, int birthNum, int x, int y);
	int countAliveNeighbours(Grid* map, int x, int y, int xVal, int yVal);
	virtual std::vector<std::vector<int>> GenerateBSP(int depthMax, int SizeInt, int minHor, int maxHor, int minVer, int maxVer);
	virtual void Split(Node* node, int depth, int maxDepth, int SizeInt, float minHor, float maxHor, float minVer, float maxVer);
	sf::Image GenerateImageBSP();
	std::vector<std::vector<int>> Generator::GenerateBSPOutput(std::vector<std::vector<int>> map);
	std::vector<std::vector<int>> CreateHall(Node* root, std::vector<std::vector<int>> curMap);
	//virtual void Render() {};
	//virtual void Load();
};