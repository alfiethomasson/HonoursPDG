#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include <iostream>
#include "Grid.h"
#include "Generator.h"
#include <random>
#include <string> 
#include <SFML/Graphics.hpp>
#include "Player.h"
#include <windows.h>

using namespace std;

sf::Sprite player;

std::vector<std::vector<int>> startAgent(std::vector<std::vector<int>> mapVec, int x, int y)
{
	mapVec.clear();
	for (int i = 0; i < x; i++)
	{
		std::vector<int> row;
		//row.reserve(32);
		for (int r = 0; r < y; r++)
		{
			row.push_back(1);
		}
		mapVec.push_back(row);
	}

	std::cout << "End of start agent " << std::endl;

	return mapVec;
}

int AgentDirection(int curDirection, int switchChance)
{
	if ((rand() % 100 + 1) <= switchChance)
	{
		std::cout << "Inside check switch chance" << std::endl;
		int pastDir = curDirection;
		while (curDirection == pastDir)
		{
			curDirection = rand() % 3;
		}
	}

	return curDirection;
}

std::vector<std::vector<int>> AgentStep(std::vector<std::vector<int>> mapVec, int point[2], int xVal, int yVal, int switchChance, bool placeRoom, int direction) // Places rooms and carves areas out of the map.
{

	if (placeRoom)
	{
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
							mapVec[point[0] + x][point[1] + y] = 0;
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
							mapVec[point[0] + x][point[1] + y] = 0;
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
							mapVec[point[0] + x][point[1] + y] = 0;
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
							mapVec[point[0] + x][point[1] + y] = 0;
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
			mapVec[point[0]][point[1] - 1] = 0;
			point[1]--;
			break;
		}
		else
		{
			break;
		}

		//East
	case 1:

		if (point[0] != (xVal - 1))
		{
			mapVec[point[0] + 1][point[1]] = 0;
			point[0]++;
			break;
		}
		else
		{
			break;
		}

		//South
	case 2:

		if (point[1] != (yVal - 1))
		{
			mapVec[point[0]][point[1] + 1] = 0;
			point[1]++;
			break;
		}
		else
		{
			break;
		}

		//West
	case 3:

		if (point[0] != 0)
		{
			mapVec[point[0] - 1][point[1]] = 0;
			point[0]--;
			break;
		}
		else
		{
			break;
		}
	}

	//std::cout << "end of this" << endl;

	return mapVec;
}


int main(int argc, char** argv)
{

	bool inMenu = true;

	//Window declaration
	sf::RenderWindow window(sf::VideoMode(800, 600), "Dungeon Generator");

	//SFML initialisations
	window.setFramerateLimit(60);
	ImGui::SFML::Init(window);
	sf::Font font;
	font.loadFromFile("res/Fonts/ARIALBD.ttf");

	sf::Clock deltaClock;

	//Loading player texture
	sf::Texture playerTex;
	if (!playerTex.loadFromFile("res/Red.png"))
	{
		std::cout << "Failed to load player texture" << endl;
	}

	//Creating player
	Player* pl = new Player(1);

	//Title text
	sf::Text title("Dungeon	Generator", font);
	sf::Text DrunkardWalkText("Cellular Automata - 1", font);
	sf::Text BSPText("Binary Space Partitioning - 2", font);
	sf::Text AgentText("Agent Based - 3", font);
	sf::Text GAText("Bounce Apart - 4", font);
	sf::Text LoadText("Load Map - 5", font);
	title.setCharacterSize(40);
	DrunkardWalkText.setCharacterSize(30);
	BSPText.setCharacterSize(30);
	AgentText.setCharacterSize(30);
	GAText.setCharacterSize(30);
	LoadText.setCharacterSize(30);
	title.setFillColor(sf::Color::White);
	DrunkardWalkText.setFillColor(sf::Color::White);
	BSPText.setFillColor(sf::Color::White);
	AgentText.setFillColor(sf::Color::White);
	GAText.setFillColor(sf::Color::White);
	LoadText.setFillColor(sf::Color::White);

	title.setPosition(200.0f, 0.0f);
	DrunkardWalkText.setPosition(225.0f, 100.0f);
	BSPText.setPosition(225.0f, 200.0f);
	AgentText.setPosition(225.0f, 300.0f);
	GAText.setPosition(225.0f, 400.0f);
	LoadText.setPosition(225.0f, 500.0f);

	//For reading in string name, used in load map
	char InputBuf[50] = { 0 };
	sf::Sprite inputSprite;
	sf::Texture inputTex;

	sf::Text SmoothText("Smooth: Off", font);
	sf::Text MipmapText("Mipmap: Off", font);

	SmoothText.setPosition(0.0f, 50.0f);
	MipmapText.setPosition(0.0f, 150.0f);

	//A lot of variables and text initialisers for the methods.

	sf::Text CAValues("CA Values", font);
	sf::Text AliveAtStartText("Start Alive %: ", font);
	sf::Text BirthNumberText("Alive neighbours for Birth: ", font);
	sf::Text IterationsText("Iterations: ", font);
	sf::Text DeathLimitText("Dead neighbours for Birth: ", font);
	sf::Text AliveInputText("", font);
	sf::Text BirthInputText("", font);
	sf::Text IterationsInputText("", font);
	sf::Text DeathText("", font);

	sf::Text BSPValues("BSP Values", font);
	sf::Text BSPDepthText("Depth: ", font);
	sf::Text BSPMinText("Minimum Split Value: ", font);
	sf::Text BSPMaxText("Maximum Split Value: ", font);

	CAValues.setCharacterSize(20);
	AliveAtStartText.setCharacterSize(20);
	BirthNumberText.setCharacterSize(20);
	IterationsText.setCharacterSize(20);
	DeathLimitText.setCharacterSize(20);

	BSPValues.setCharacterSize(20);
	BSPDepthText.setCharacterSize(20);
	BSPMinText.setCharacterSize(20);
	BSPMaxText.setCharacterSize(20);

	CAValues.setFillColor(sf::Color::White);
	AliveAtStartText.setFillColor(sf::Color::White);
	BirthNumberText.setFillColor(sf::Color::White);
	IterationsText.setFillColor(sf::Color::White);
	DeathLimitText.setFillColor(sf::Color::White);

	BSPValues.setFillColor(sf::Color::White);
	BSPDepthText.setFillColor(sf::Color::White);
	BSPMinText.setFillColor(sf::Color::White);
	BSPMaxText.setFillColor(sf::Color::White);

	CAValues.setPosition(50.0f, 0.0f);
	AliveAtStartText.setPosition(50.0f, 50.0f);
	BirthNumberText.setPosition(250.0f, 50.0f);
	IterationsText.setPosition(50.0f, 100.0f);
	DeathLimitText.setPosition(250.0f, 100.0f);

	sf::FloatRect AliveAtStartBox(50.0f, 50.0f, 150.0f, 40.0f);
	sf::FloatRect BirthNumberBox(350.0f, 50.0f, 200.0f, 40.0f);
	sf::FloatRect IterationsBox(50.0f, 100.0f, 150.0f, 40.0f);
	sf::FloatRect DeathLimitBox(350.0f, 100.0f, 200.0f, 40.0f);

	AliveInputText.setPosition(50.0f + AliveAtStartText.getGlobalBounds().width, 40.0f);
	BirthInputText.setPosition(50.0f + BirthNumberText.getGlobalBounds().width, 40.0f);
	IterationsInputText.setPosition(50.0f + IterationsText.getGlobalBounds().width, 90.0f);
	DeathText.setPosition(50.0f + DeathLimitText.getGlobalBounds().width, 90.0f);


	sf::String methodName = "Test";
	Generator* gen = new Generator(methodName, 50, 50);

	std::vector<std::vector<int>> BSPGrid;
	std::vector<std::vector<int>> AgentGrid;
	std::vector<std::vector<int>> BounceGrid;
	std::vector<std::vector<int>> saveMap;
	std::vector<std::vector<int>> caGrid;

	for (int i = 0; i < BSPGrid.size(); i++)
	{
		for (int y = 0; y < BSPGrid[i].size(); y++)
		{
			std::cout << " " << BSPGrid[i][y];
		}
		std::cout << std::endl;
	}

	//Initialisation of the tilemaps
	TileMap caMap;
	TileMap bspMap;
	TileMap agentMap;
	TileMap inputMap;
	TileMap bounceMap;

	bool bspActive = false; 
	bool drunkardwalkActive = false;
	bool agentActive = false;
	bool agentWorking = false;
	bool loadActive = false;
	bool bounceActive = false;
	bool playerViewActive = false;
	bool agentWeight = false;

	bool playerActive = false;
	bool placeRoomBool = false;

	bool smoothOn = false;
	bool mipmapOn = false;

	int direction;
	int switchWeight = 0;
	int curAgentIter = 0;
	int weightIterations = 1;
	int weightVal = 1;
	bool straightAgent = false;
	int minStraightLength = 2;
	int straightLength = 0;

	sf::View mainView(sf::FloatRect(0.f, 0.f, 800.0f, 600.f));

	window.setView(mainView);
	float curZoom = 1.f;

	sf::View playerView(sf::FloatRect(0.f, 0.f, 800.f, 600.f));

	sf::Image output;

	sf::String playerInput;
	sf::Text inputText;

	int SizeInt = 50;

	int AliveInt = 42;
	int BirthInt = 4;
	int IterationsInt = 2;
	int DeathInt = 3;

	int depthInt = 5;
	int minHorInt = 40;
	int maxHorInt = 60;
	int minVerInt = 40;
	int maxVerInt = 60;

	int switchInt = 5;
	int roomInt = 5;
	int IterationsAgentInt = 100;
	//int roomXInt = 

	int bounceDist = 10;
	int bounceRooms = 20;
	int bounceRadius = 10;
	int bounceRoomMax = 8;
	int bounceRoommin = 2;

	double startTime;
	int agentPoint[2];

	inputText.setFont(font);
	inputText.setCharacterSize(30);
	inputText.setPosition(0.0f, 0.0f);

	gen->Reset(SizeInt, SizeInt, AliveInt);

	//Seed
	srand(2000);

	//Runs every frame while application is running
	while (window.isOpen())
	{
		//Gets mouse pos
		sf::Vector2i tempPos = sf::Mouse::getPosition(window);
		sf::Vector2f cursPos = sf::Vector2f(tempPos);

		sf::Event event;

		//SFML events
		while (window.pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(event);
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::TextEntered)
			{

				if (AliveAtStartBox.contains(cursPos))
				{
					sf::String curString = AliveInputText.getString();
					if (event.text.unicode == '\b')
					{
						curString.erase(curString.getSize() - 1, 1);
					}
					else
					{
						curString += event.text.unicode;
					}
					AliveInputText.setString(curString);
				}
				else if (BirthNumberBox.contains(cursPos))
				{
					sf::String curString = BirthInputText.getString();
					if (event.text.unicode == '\b')
					{
						curString.erase(curString.getSize() - 1, 1);
					}
					else
					{
						curString += event.text.unicode;
					}
					BirthInputText.setString(curString);
				}
				else if (IterationsBox.contains(cursPos))
				{
					sf::String curString = IterationsInputText.getString();
					if (event.text.unicode == '\b')
					{
						curString.erase(curString.getSize() - 1, 1);
					}
					else
					{
						curString += event.text.unicode;
					}
					IterationsInputText.setString(curString);
				}
				else if (DeathLimitBox.contains(cursPos))
				{
					sf::String curString = DeathText.getString();
					if (event.text.unicode == '\b')
					{
						curString.erase(curString.getSize() - 1, 1);
					}
					else
					{
						curString += event.text.unicode;
					}
					DeathText.setString(curString);
				}
			}


			//Zoom
			if (event.type == sf::Event::MouseWheelMoved && !inMenu)
			{
				//std::cout << event.mouseWheel.delta << std::endl;
				int wheelMovement = event.mouseWheel.delta;
				if (wheelMovement == 1)
				{
					mainView.zoom(curZoom - 0.05f);
					curZoom -= 0.01f;
					if (curZoom < 0.0f)
					{
						curZoom = 0.0f;
					}
				}
				else
				{
					mainView.zoom(curZoom + 0.05f);
					curZoom += 0.01f;
					if (curZoom > 1.0f)
					{
						curZoom = 1.0f;
					}
				}
				window.setView(mainView);
			}

			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		ImGui::SFML::Update(window, deltaClock.restart());

		//If in menu check for moving to methods.
		if (inMenu)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
			{
				inMenu = false;
				drunkardwalkActive = true;
				mainView.reset(sf::FloatRect(0.0f, 0.0f, 800.0f, 600.0f));
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
			{
				inMenu = false;
				bspActive = true;
				mainView.reset(sf::FloatRect(0.0f, 0.0f, 800.0f, 600.0f));
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
			{
				inMenu = false;
				agentActive = true;
				mainView.reset(sf::FloatRect(0.0f, 0.0f, 800.0f, 600.0f));
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
			{
				inMenu = false;
				bounceActive = true;
				mainView.reset(sf::FloatRect(0.0f, 0.0f, 800.0f, 600.0f));
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
			{
				inMenu = false;
				loadActive = true;
				mainView.reset(sf::FloatRect(0.0f, 0.0f, 800.0f, 600.0f));
			}

			window.clear();


			window.draw(title);
			window.draw(DrunkardWalkText);
			window.draw(BSPText);
			window.draw(AgentText);
			window.draw(GAText);
			window.draw(LoadText);

		}
		else // In a method
		{
			
			ImGui::Begin("Generator Options");
			ImGui::SliderInt("Size", &SizeInt, 20.0, 500.0);


			if (drunkardwalkActive) // Named drunkard walk, this is CA!
			{

				ImGui::SliderInt("% To Start Alive", &AliveInt, 1.0, 100.0);
				ImGui::SliderInt("Neighbours to Birth Cell", &BirthInt, 0.0, 9.0);
				ImGui::SliderInt("Iterations", &IterationsInt, 0.0, 50.0);
				ImGui::SliderInt("Neighbours to Kill Cell", &DeathInt, 0.0, 9.0);

				if (playerActive)
				{
					pl->Update(caGrid, SizeInt);
				}

				if (ImGui::Button("Spawn Player"))
				{
					caGrid = gen->FindEndpoint(caGrid);
					if (!caMap.load("res/Tilesets/Tileset.png", sf::Vector2u(32, 32), caGrid, SizeInt, SizeInt))
					{
						cout << "Failed to load tileset" << endl;
					}
					caMap.EnableMipMap(true);
					pl->Load(0, 0, false, caGrid);
					playerActive = true;
				}

				if (ImGui::Button("Black Background"))
				{
					caGrid = gen->ChangeToBlack(caGrid);
					if (!caMap.load("res/Tilesets/Tileset.png", sf::Vector2u(32, 32), caGrid, SizeInt, SizeInt))
					{
						cout << "Failed to load tileset" << endl;
					}
					caMap.EnableMipMap(true);
				}
			}
			else if (bspActive) //Space partitioning
			{

				ImGui::SliderInt("Depth", &depthInt, 1.0, 5.0);
				ImGui::SliderInt("Minimum Horizontal Split", &minHorInt, 0.0, 100.0);
				ImGui::SliderInt("Maximum Horizontal Split", &maxHorInt, 0.0, 100.0);
				ImGui::SliderInt("Minimum Vertical Split", &minVerInt, 0.0, 100.0);
				ImGui::SliderInt("Maximum Vertical Split", &maxVerInt, 0.0, 100.0);

				if (ImGui::Button("Spawn Player"))
				{
					BSPGrid = gen->FindEndpoint(BSPGrid);
					if (!bspMap.load("res/Tilesets/Tileset.png", sf::Vector2u(32, 32), BSPGrid, SizeInt, SizeInt))
					{
						cout << "Failed to load tileset" << endl;
					}
					bspMap.EnableMipMap(true);
					pl->Load(0, 0, false, BSPGrid);
					playerActive = true;
				}

				if (playerActive)
				{
					pl->Update(BSPGrid, SizeInt);
				}

				if (ImGui::Button("Do Room Size"))
				{
					BSPGrid = gen->BSPRandomRooms(BSPGrid);
					if (!bspMap.load("res/Tilesets/Tileset.png", sf::Vector2u(32, 32), BSPGrid, SizeInt, SizeInt))
					{
						cout << "Failed to load tileset" << endl;
					}
					bspMap.EnableMipMap(true);
				}

				if (ImGui::Button("AddCorridors"))
				{
					BSPGrid = gen->AddCorridors(SizeInt);

					if (!bspMap.load("res/Tilesets/Tileset.png", sf::Vector2u(32, 32), BSPGrid, SizeInt, SizeInt))
					{
						cout << "Failed to load tileset" << endl;
					}

					bspMap.EnableMipMap(true);
				}

				if (ImGui::Button("Black Background"))
				{
					BSPGrid = gen->ChangeToBlack(BSPGrid);
					if (!bspMap.load("res/Tilesets/Tileset.png", sf::Vector2u(32, 32), BSPGrid, SizeInt, SizeInt))
					{
						cout << "Failed to load tileset" << endl;
					}
					bspMap.EnableMipMap(true);
				}

			}
			else if (agentActive) // Agent
			{
				ImGui::SliderInt("Switch Chance %", &switchInt, 1.0, 100.0);
				ImGui::SliderInt("Room Chance %", &roomInt, 1.0, 100.0);
				ImGui::SliderInt("Iterations", &IterationsAgentInt, 1.0, 1000.0);
				if (agentWeight) //Enable/disable switchweight
				{
					if (ImGui::Button("Disable Switch Weight"))
					{
						agentWeight = !agentWeight;
					}
				}
				else
				{
					if (ImGui::Button("Enable Switch Weight"))
					{
						agentWeight = !agentWeight;
					}
				}
				if (agentWeight)
				{
					ImGui::SliderInt("Look Ahead Weight", &weightVal, 1.0, 100.0);
					ImGui::SliderInt("Look Ahead Iterations", &weightIterations, 1.0, 10);
				}
				if (ImGui::Button("Enable Minimum Straight Lines")) //minimum straight
				{
					straightAgent = !straightAgent;
				}

				if (straightAgent)
				{
					ImGui::SliderInt("Minimum Straight Length", &minStraightLength, 1.0, 10.0);
				}

				if (ImGui::Button("Spawn Player"))
				{
					AgentGrid = gen->FindEndpoint(AgentGrid);
					if (!agentMap.load("res/Tilesets/Tileset.png", sf::Vector2u(32, 32), AgentGrid, SizeInt, SizeInt))
					{
						cout << "Failed to load tileset" << endl;
					}
					agentMap.EnableMipMap(true);
					pl->Load(0, 0, false, AgentGrid);
					playerActive = true;
				}

				if (ImGui::Button("Black Background"))
				{
					AgentGrid = gen->ChangeToBlack(AgentGrid);
					if (!agentMap.load("res/Tilesets/Tileset.png", sf::Vector2u(32, 32), AgentGrid, SizeInt, SizeInt))
					{
						cout << "Failed to load tileset" << endl;
					}
					agentMap.EnableMipMap(true);
				}

				if (playerActive)
				{
					pl->Update(AgentGrid, SizeInt);
				}

				if (agentWorking) // IF AGENT IS RUNNING
				{
					double currentTime = GetTickCount() - startTime;

					if (curAgentIter < IterationsAgentInt)
					{
						if (currentTime >= 5.0)
						{
							//	direction = AgentDirection(direction, switchInt);
							curAgentIter++;

							switchWeight = 0;
							if (straightLength > minStraightLength || !straightAgent) // if switch weight is enabled 
							{
								if (agentWeight)
								{
									for (int i = 1; i < (weightIterations + 1); i++)
									{
										switch (direction)
										{
										case 0:
											if (agentPoint[1] - i > 0)
											{
												if (AgentGrid[agentPoint[0]][agentPoint[1] - i] == 1)
												{
													switchWeight += weightVal;
												}
											}
										case 1:
											if (agentPoint[0] + i < SizeInt)
											{
												if (AgentGrid[agentPoint[0] + i][agentPoint[1]] == 1)
												{
													switchWeight += weightVal;
												}
											}
										case 2:
											if (agentPoint[1] + i < SizeInt)
											{
												if (AgentGrid[agentPoint[0]][agentPoint[1] + i] == 1)
												{
													switchWeight += weightVal;
												}
											}
										case 3:
											if (agentPoint[0] - i > 0)
											{
												if (AgentGrid[agentPoint[0] - i][agentPoint[1]] == 1)
												{
													switchWeight += weightVal;
												}
											}
										}
									}
								}

								if ((rand() % 100 + 1) <= switchInt + switchWeight) // Check if switch
								{
									int pastDir = direction;
									while (direction == pastDir)
									{
										direction = rand() % 3;
									}
									straightLength = 0;
									switchWeight = 0;
								}

							}

							//If on one of the walls, change direction
							if (agentPoint[0] == 0 && direction == 3)
							{
								direction = 1;
							}
							else if (agentPoint[0] == AgentGrid.size() - 1 && direction == 1)
							{
								direction = 3;
							}
							else if (agentPoint[1] == 0 && direction == 0)
							{
								direction = 2;
							}
							else if (agentPoint[1] == AgentGrid.size() - 1 && direction == 2)
							{
								direction = 0;
							}

							if ((rand() % 100 + 1) <= roomInt) // Check if place room
							{
								int pastDir;
								switch (direction)
								{
								case 0:
									pastDir = 2;

								case 1:
									pastDir = 3;

								case 2:
									pastDir = 0;

								case 3:
									pastDir = 1;
								}
								while (direction == pastDir)
								{
									direction = rand() % 3;
								}
								placeRoomBool = true;
							}
							else
							{
								placeRoomBool = false;
							}
							straightLength++;
							AgentGrid = AgentStep(AgentGrid, agentPoint, SizeInt, SizeInt, switchInt, placeRoomBool, direction); // Digger function
							//AgentGrid = gen->ChangeToBlack(AgentGrid);
							startTime = GetTickCount();
							if (!agentMap.load("res/Tilesets/Tileset.png", sf::Vector2u(32, 32), AgentGrid, SizeInt, SizeInt))
							{
								cout << "Failed to load tileset" << endl;
							}
							agentMap.EnableMipMap(true);
						}
					}
					else
					{
						agentWorking = false;
					}
				}

				if (ImGui::Button("Start Agent")) //Starts the agent
				{
					if (agentWorking)
					{
						agentWorking = false;
					}
					else
					{
						//Initialisors
						srand(2000);
						curAgentIter = 0;
						AgentGrid = startAgent(AgentGrid, SizeInt, SizeInt);

						int ran1 = rand() % ((SizeInt / 2) + (SizeInt / 4)) + (SizeInt / 4);
						int ran2 = rand() % ((SizeInt / 2) + (SizeInt / 4)) + (SizeInt / 4);

						int randPoint[2];
						randPoint[0] = ran1;
						//std::cout << "Rand point 0 = " << randPoint[0] << std::endl;
						randPoint[1] = ran2;
						agentPoint[0] = randPoint[0];
						agentPoint[1] = randPoint[1];

						std::uniform_int_distribution<> dir(0, 3);
						direction = rand() % 3;

						startTime = GetTickCount();
						agentWorking = true;
					}
				}
			}
			else if (bounceActive) // Constraint based (bounce)
			{

				ImGui::SliderInt("Number of Rooms", &bounceRooms, 1.0, 50);
				ImGui::SliderInt("Radius to spawn Rooms", &bounceRadius, 5.0, 30.0);
				ImGui::SliderInt("Minimum Room Size", &bounceRoommin, 1.0, 20.0);
				ImGui::SliderInt("Maximum Room Size", &bounceRoomMax, 1.0, 20.0);
				ImGui::SliderInt("Maximum Distance to spawn corridor", &bounceDist, 5.0, 30.0);

				if (playerActive)
				{
					pl->Update(BounceGrid, SizeInt);
				}

				if (ImGui::Button("Add Corridors"))
				{
					BounceGrid = gen->ConstraintCorridors(100, 100, bounceDist);

					if (!bounceMap.load("res/Tilesets/Tileset.png", sf::Vector2u(32, 32), BounceGrid, 100, 100))
					{
						cout << "Failed to load tileset" << endl;
					}
					bounceMap.EnableMipMap(true);
				}

				if (ImGui::Button("Spawn Player"))
				{
					BounceGrid = gen->FindEndpoint(BounceGrid);
					if (!bounceMap.load("res/Tilesets/Tileset.png", sf::Vector2u(32, 32), BounceGrid, 100, 100))
					{
						cout << "Failed to load tileset" << endl;
					}
					bounceMap.EnableMipMap(true);
					pl->Load(0, 0, false, BounceGrid);
					playerActive = true;
				}

				if (ImGui::Button("Black Background"))
				{
					BounceGrid = gen->ChangeToBlack(BounceGrid);
					if (!bounceMap.load("res/Tilesets/Tileset.png", sf::Vector2u(32, 32), BounceGrid, 100, 100))
					{
						cout << "Failed to load tileset" << endl;
					}
					bounceMap.EnableMipMap(true);
				}
			}
			else if (loadActive) //Load map
				{
				ImGui::InputText("File Path", InputBuf, IM_ARRAYSIZE(InputBuf));

				if (ImGui::Button("Load From File"))  //Reads filepath from entered text and loads map from that
				{
					sf::String fp;
					fp += "D:/SaveImages/";
					sf::String png;
					png += ".png";

					fp += InputBuf;
					fp += png;
					sf::Image testImg;
					testImg.loadFromFile(fp);

					std::vector<std::vector<int>> loadGrid;

					for (int i = 0; i < testImg.getSize().x; i++)
					{
						std::vector<int> row;
						for (int y = 0; y < testImg.getSize().y; y++)
						{
							if (testImg.getPixel(i, y) == sf::Color::Black)
							{
								row.push_back(1);
							}
							else if (testImg.getPixel(i, y) == sf::Color::White)
							{
								row.push_back(0);
							}
						}
						loadGrid.push_back(row);
					}

					if (!inputMap.load("res/Tilesets/Tileset.png", sf::Vector2u(32, 32), loadGrid, testImg.getSize().x, testImg.getSize().y))
					{
						cout << "Failed to load tileset" << endl;
					}
					inputMap.EnableMipMap(true);

					saveMap = loadGrid;
				}

				if (ImGui::Button("Default Load")) //Testload
				{
					sf::Image testImg;
					testImg.loadFromFile("D:/SaveImages/SavedImage.png");

					std::vector<std::vector<int>> loadGrid;

					for (int i = 0; i < testImg.getSize().x; i++)
					{
						std::vector<int> row;
						for (int y = 0; y < testImg.getSize().y; y++)
						{
							if (testImg.getPixel(i, y) == sf::Color::Black)
							{
								row.push_back(1);
							}
							else if (testImg.getPixel(i, y) == sf::Color::White)
							{
								row.push_back(0);
							}
						}
						loadGrid.push_back(row);
					}

					if (!inputMap.load("res/Tilesets/Tileset.png", sf::Vector2u(32, 32), loadGrid, testImg.getSize().x, testImg.getSize().y))
					{
						cout << "Failed to load tileset" << endl;
					}
					inputMap.EnableMipMap(true);

					saveMap = loadGrid;
				}

				if (ImGui::Button("Spawn Player"))
				{
					saveMap = gen->FindEndpoint(saveMap);
					if (!inputMap.load("res/Tilesets/Tileset.png", sf::Vector2u(32, 32), saveMap, saveMap.size(), saveMap.size()))
					{
						cout << "Failed to load tileset" << endl;
					}
					inputMap.EnableMipMap(true);
					pl->Load(0, 0, false, saveMap);
					playerActive = true;
				}

				if (playerActive)
				{
					pl->Update(saveMap, SizeInt);
				}

			}


			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				mainView.move(-10.f * (curZoom), 0.f);
				window.setView(mainView);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				mainView.move(10.f * (curZoom), 0.f);
				window.setView(mainView);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				mainView.move(0.f, 10.f * (curZoom));
				window.setView(mainView);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				mainView.move(0.f, -10.f * (curZoom));
				window.setView(mainView);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) //Back to menu
			{
				drunkardwalkActive = false;
				bspActive = false;
				agentActive = false;
				loadActive = false;
				playerActive = false;
				inMenu = true;
				mainView.reset(sf::FloatRect(0.0f, 0.0f, 800.0f, 600.0f));
				mainView.zoom(1.0f + (curZoom * 0.05));
				window.setView(mainView);
			}
			if (!loadActive)
			{
				if (ImGui::Button("Reset"))
				{
					gen->Reset(SizeInt, SizeInt, AliveInt);
				}

				if (ImGui::Button("Step")) // Steps through the next iteration of a method
				{
					if (drunkardwalkActive)
					{
						srand(time(0));
						caGrid = gen->GenerateMapTiles(SizeInt, SizeInt, AliveInt, BirthInt, IterationsInt, DeathInt, 1, true, 1);
						if (!caMap.load("res/Tilesets/Tileset.png", sf::Vector2u(32, 32), caGrid, SizeInt, SizeInt))
						{
							cout << "Failed to load tileset" << endl;
						}
						caMap.EnableMipMap(true);
					}
					if (bspActive)
					{
						BSPGrid = gen->GenerateBSP(depthInt, SizeInt, minHorInt, maxHorInt, minVerInt, maxVerInt, true, 1);

						if (!bspMap.load("res/Tilesets/Tileset.png", sf::Vector2u(32, 32), BSPGrid, SizeInt, SizeInt))
						{
							cout << "Failed to load tileset" << endl;
						}
						bspMap.EnableMipMap(true);
					}
					if (bounceActive)
					{
						BounceGrid = gen->GenerateConstraint(100, 100, true, 1, bounceRoomMax, bounceRoommin, bounceRooms, bounceRadius);

						if (!bounceMap.load("res/Tilesets/Tileset.png", sf::Vector2u(32, 32), BounceGrid, SizeInt, SizeInt))
						{
							cout << "Failed to load tileset" << endl;
						}
						bounceMap.EnableMipMap(true);
					}
				}

				if (ImGui::Button("Generate Full")) //Generates full output based on parameters
				{
					if (drunkardwalkActive)
					{
						//srand(1000);
						caGrid = gen->GenerateMapTiles(SizeInt, SizeInt, AliveInt, BirthInt, IterationsInt, DeathInt, 1, false, IterationsInt);
						if (!caMap.load("res/Tilesets/Tileset.png", sf::Vector2u(32, 32), caGrid, SizeInt, SizeInt))
						{
							cout << "Failed to load tileset" << endl;
						}
						caMap.EnableMipMap(true);
					}
					else if (bspActive)
					{
						gen->Reset(SizeInt, SizeInt, AliveInt);
						BSPGrid = gen->GenerateBSP(depthInt, SizeInt, minHorInt, maxHorInt, minVerInt, maxVerInt, false, depthInt);

						if (!bspMap.load("res/Tilesets/Tileset.png", sf::Vector2u(32, 32), BSPGrid, SizeInt, SizeInt))
						{
							cout << "Failed to load tileset" << endl;
						}
						bspMap.EnableMipMap(true);
					}
					else if (agentActive)
					{
						AgentGrid = gen->GenerateAgent(SizeInt, SizeInt, switchInt, roomInt, IterationsAgentInt);

						if (!agentMap.load("res/Tilesets/Tileset.png", sf::Vector2u(32, 32), AgentGrid, SizeInt, SizeInt))
						{
							cout << "Failed to load tileset" << endl;
						}
						agentMap.EnableMipMap(true);
					}
					else if (bounceActive)
					{
						BounceGrid = gen->GenerateConstraint(100, 100, false, 5, bounceRoomMax, bounceRoommin, bounceRooms, bounceRadius);
						if (!bounceMap.load("res/Tilesets/Tileset.png", sf::Vector2u(32, 32), BounceGrid, 100, 100))
						{
							cout << "Failed to load tileset" << endl;
						}
						bounceMap.EnableMipMap(true);
					}
				}

				if (ImGui::Button("Save Map")) // Saves the current map 
				{
					sf::Image saveImage;
					saveImage.create(SizeInt * 10, SizeInt * 10, sf::Color::Black);

					std::vector<std::vector<int>> saveMap;
					for (int i = 0; i < SizeInt; i++)
					{
						std::vector<int> row;
						for (int y = 0; y < SizeInt; y++)
						{
							int cellVal;
							if (drunkardwalkActive)
							{
								std::cout << "Pushing: " << caGrid[i][y] << std::endl;
								row.push_back(caGrid[i][y]);
								cellVal = caGrid[i][y];
							}
							else if (bspActive)
							{
								row.push_back(BSPGrid[i][y]);
								cellVal = BSPGrid[i][y];
							}
							else if (agentActive)
							{
								row.push_back(AgentGrid[i][y]);
								cellVal = AgentGrid[i][y];
							}
							else if (bounceActive)
							{
								row.push_back(BounceGrid[i][y]);
								cellVal = BounceGrid[i][y];
							}

							if (i != SizeInt && y != SizeInt)
							{
								for (int x = 0; x < 10; x++)
								{
									for (int r = 0; r < 10; r++)
									{
										if (cellVal == 0)
										{
											saveImage.setPixel((i * 10) + x, (y * 10) + r, sf::Color::White);
										}
										else if (cellVal == 1)
										{
											saveImage.setPixel((i * 10) + x, (y * 10) + r, sf::Color::Black);
										}
									}
								}
							}
						}
						saveMap.push_back(row);
					}

					int saveNum1 = rand() % 9;
					int saveNum2 = rand() % 9;
					int saveNum3 = rand() % 9;
					int saveNum4 = rand() % 9;
					int saveNum5 = rand() % 9;

					sf::String ranSeed;
					ranSeed += std::to_string(saveNum1);
					ranSeed += std::to_string(saveNum2);
					ranSeed += std::to_string(saveNum3);
					ranSeed += std::to_string(saveNum4);
					ranSeed += std::to_string(saveNum5);

					if (drunkardwalkActive)
					{
						saveImage.saveToFile("D:/SaveImages/CASave" + ranSeed + ".png");
					}
					if (bspActive)
					{
						saveImage.saveToFile("D:/SaveImages/BSPSave" + ranSeed + ".png");
					}
					if (agentActive)
					{
						saveImage.saveToFile("D:/SaveImages/AgentSave" + ranSeed + ".png");
					}
					if (bounceActive)
					{
						saveImage.saveToFile("D:/SaveImages/ConstraintSave" + ranSeed + ".png");
					}
				}
			}

			if (playerActive) 
			{
				playerView.setCenter(pl->GetPos());

				if (ImGui::Button("Switch Camera View"))
				{
					playerViewActive = !playerViewActive;
				}
				if (playerViewActive)
				{
					window.setView(playerView);
				}
				else
				{
					window.setView(mainView);
				}
			}

			window.clear();

			

			if (drunkardwalkActive)
			{
				window.draw(caMap);
			}
			else if (bspActive)
			{
				window.draw(bspMap);
			}
			else if (agentActive)
			{
				window.draw(agentMap);
			}
			else if (bounceActive)
			{
				window.draw(bounceMap);
			}
			else if (loadActive)
			{
				window.draw(inputMap);
			}

			if (playerActive)
			{
				window.draw(pl->GetSprite());
			}

			ImGui::End();
		}
		ImGui::SFML::Render(window);
		window.display();
	}

	return 0;
}
