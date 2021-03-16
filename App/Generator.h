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

	int parentSplit;
};

class Generator {
protected:
	sf::String method;
	//std::vector<std::vector<int>> dungeon;
	int xSize;
	int ySize;

	sf::Image pixels;

	std::vector<Node*> rooms;

	std::vector<std::vector<int>> stepVecMap;
	Grid* stepMap;

	Node* stepRoot;
	std::vector<std::vector<int>> stepRooms;
	int bounceStep;

	float storedAliveChance;
	int storedBirthNum;
	int storedDeathLimit;
	int curIteration;

	int totalBSPIterations;

	int prevSplit;

public:
	Generator(sf::String methodType, int x, int y) { xSize = x, ySize = y, method = methodType;};
	virtual ~Generator() = default;

	virtual sf::Image GenerateDungeon(int caMap[], int iterations, int type);
	void Reset(int x, int y, int alivePercent);
	std::vector<std::vector<int>> Generator::GenerateMapTiles(int x, int y, int AlivePercent, int BirthNum, int iterations, int DeathLimit, int type, bool stepBool, int numberIterations);
	Grid* CAIteration(Grid* oldMap, std::vector<std::vector<int>> tileMap, int deathNum, int birthNum, int x, int y);
	int countAliveNeighbours(Grid* map, int x, int y, int xVal, int yVal);
	virtual std::vector<std::vector<int>> GenerateBSP(int depthMax, int SizeInt, int minHor, int maxHor, int minVer, int maxVer, bool stepActive, int stepDepth);
	virtual void Split(Node* node, int depth, int maxDepth, int SizeInt, float minHor, float maxHor, float minVer, float maxVer, int totalIterations, bool doAll);
	sf::Image GenerateImageBSP();
	std::vector<std::vector<int>> AddCorridors(int SizeInt);
	std::vector<std::vector<int>> Generator::GenerateBSPOutput(std::vector<std::vector<int>> map);
	std::vector<std::vector<int>> Generator::BSPRandomRooms(std::vector<std::vector<int>> map);
	std::vector<std::vector<int>> CreateHall(Node* root, std::vector<std::vector<int>> curMap);
	virtual std::vector<std::vector<int>> GenerateAgent(int x, int y, int switchChance, int roomChance, int iterations);
	std::vector<int> getRandomPoint(int radius);
	std::vector<std::vector<int>> GenerateConstraint(int x, int y, bool stepActive, int noIter, int roomMax, int roomMin, int noRooms, int radius);
	std::vector<std::vector<int>> ConstraintGraph(int x, int y);
	std::vector<std::vector<int>> ConstraintCorridors(int x, int y, int bounceDist);
	std::vector<std::vector<int>> Generator::FindEndpoint(std::vector<std::vector<int>> input);
	std::vector<std::vector<int>> ChangeToBlack(std::vector<std::vector<int>> input);
	//virtual void Render() {};
	//virtual void Load();
};