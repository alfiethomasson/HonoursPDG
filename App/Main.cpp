#include <iostream>
#include "Grid.h"
#include "Generator.h"
#include <random>
#include <string> 
#include <SFML/Graphics.hpp>
#include "TileMap.h"

using namespace std;


int main(int argc, char** argv)
{

	bool inMenu = true;

	sf::RenderWindow window(sf::VideoMode(800, 600), "Dungeon Generator");
	//sf::CircleShape shape(100.f);
	sf::Font font;
	font.loadFromFile("D:/fonts/ARIALBD.ttf");
	sf::Text title("Dungeon	Generator", font);
	sf::Text DrunkardWalkText("Cellular Automata - 1", font);
	sf::Text BSPText("Binary Space Partitioning - 2", font);
	sf::Text AgentText("Agent Based - 3", font);
	sf::Text GAText("Genetic Algorithm - 4", font);
	title.setCharacterSize(40);
	DrunkardWalkText.setCharacterSize(30);
	BSPText.setCharacterSize(30);
	AgentText.setCharacterSize(30);
	GAText.setCharacterSize(30);
	title.setFillColor(sf::Color::White);
	DrunkardWalkText.setFillColor(sf::Color::White);
	BSPText.setFillColor(sf::Color::White);
	AgentText.setFillColor(sf::Color::White);
	GAText.setFillColor(sf::Color::White);

	title.setPosition(200.0f, 0.0f);
	DrunkardWalkText.setPosition(225.0f, 100.0f);
	BSPText.setPosition(225.0f, 200.0f);
	AgentText.setPosition(225.0f, 300.0f);
	GAText.setPosition(225.0f, 400.0f);

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
	Generator* gen = new Generator(methodName, 30, 30);
	//std::vector<std::vector<int>> caGrid = gen->GenerateMapTiles(10, 10, 100, 1);
	std::vector<std::vector<int>> BSPGrid;

	std::vector<std::vector<int>> caGrid;

	std::cout << "Before tilemap load" << std::endl;

	std::cout << "RESULT GRID: " << std::endl;
	for (int i = 0; i < BSPGrid.size(); i++)
	{
		for (int y = 0; y < BSPGrid[i].size(); y++)
		{
			std::cout << " " << BSPGrid[i][y];
		}
		std::cout << std::endl;
	}

	TileMap caMap;
	TileMap bspMap;
	/*if (!caMap.load("D:/Github/HonoursPDG/TilesetTest.png", sf::Vector2u(32, 32), BSPGrid, 30, 30))
	{
		cout << "Failed to load tileset" << endl;
	}*/

	std::cout << "After tilemap load" << std::endl;

	bool bspActive = false; 
	bool drunkardwalkActive = false;

	sf::View mainView(sf::FloatRect(0.f, 0.f, 800.f, 600.f));

	window.setView(mainView);
	float curZoom = 1.f;

	sf::Image output;
	//output = gen->GenerateDungeon(caGrid, 100, 1);

	//output = gen->GenerateBSP();
	//sf::Texture imgText;
	//imgText.loadFromImage(output);

	//sf::Sprite dungeon;
	//dungeon.setTexture(imgText);

	//dungeon.setPosition(0, 0);

	sf::String playerInput;
	sf::Text inputText;

	inputText.setFont(font);
	inputText.setCharacterSize(30);
	inputText.setPosition(0.0f, 0.0f);

	while (window.isOpen())
	{
		sf::Vector2i tempPos = sf::Mouse::getPosition(window);
		sf::Vector2f cursPos = sf::Vector2f(tempPos);

		if (AliveAtStartBox.contains(cursPos))
		{

		}
		else if (BirthNumberBox.contains(cursPos))
		{

		}
		else if (IterationsBox.contains(cursPos))
		{

		}
		else if (DeathLimitBox.contains(cursPos))
		{

		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseWheelMoved)
			{
				//std::cout << event.mouseWheel.delta << std::endl;
				int wheelMovement = event.mouseWheel.delta;
				if (wheelMovement == 1)
				{
					mainView.zoom(curZoom - 0.05f);
				}
				else
				{
					mainView.zoom(curZoom + 0.05f);
				}
				window.setView(mainView);
			}

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
		}

		if (inMenu)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
			{
				inMenu = false;
				drunkardwalkActive = true;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
			{
				inMenu = false;
				bspActive = true;
			}
			//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
			//{
			//	output = gen->GenerateBSP();
			//	imgText.loadFromImage(output);
			//	dungeon.setTexture(imgText);

			//	inMenu = false;
			//	bspActive = true;
			//}
			window.clear();


			window.draw(title);
			window.draw(DrunkardWalkText);
			window.draw(BSPText);
			window.draw(AgentText);
			window.draw(GAText);



			//window.draw(caMap);

		}
		else
		{

			if (drunkardwalkActive)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
				{
					std::string AliveString = AliveInputText.getString();
					std::cout << "Trying to convert string: " << AliveString << std::endl;
					std::string BirthString = BirthInputText.getString();
					std::string IterationsString = IterationsInputText.getString();
					std::string DeathLimitString = DeathText.getString();
					int AlivePercent = std::stoi(AliveString);
					std::cout << "Converted string: " << AlivePercent << std::endl;
					int BirthNum = std::stoi(BirthString);
					int iterations = std::stoi(IterationsString);
					int DeathLimit = std::stoi(DeathLimitString);
					caGrid = gen->GenerateMapTiles(30, 30, AlivePercent, BirthNum, iterations, DeathLimit, 1);
					if (!caMap.load("D:/Github/HonoursPDG/TilesetTest.png", sf::Vector2u(32, 32), caGrid, 30, 30))
					{
						cout << "Failed to load tileset" << endl;
					}
					//imgText.loadFromImage(output);
					//dungeon.setTexture(imgText);

				}
			}
			else if (bspActive)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
				{
					BSPGrid = gen->GenerateBSP();

					if (!bspMap.load("D:/Github/HonoursPDG/TilesetTest.png", sf::Vector2u(32, 32), BSPGrid, 30, 30))
					{
						cout << "Failed to load tileset" << endl;
					}
				}
			}


			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				mainView.move(-1.f * (curZoom * 0.1f), 0.f);
				window.setView(mainView);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				mainView.move(1.f * (curZoom * 0.1f), 0.f);
				window.setView(mainView);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				mainView.move(0.f, 1.f * (curZoom * 0.1f));
				window.setView(mainView);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				mainView.move(0.f, -1.f * (curZoom * 0.1f));
				window.setView(mainView);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				drunkardwalkActive = false;
				bspActive = false;
				inMenu = true;
			}

			window.clear();


			if (drunkardwalkActive)
			{
				window.draw(CAValues);
				window.draw(AliveAtStartText);
				window.draw(BirthNumberText);
				window.draw(IterationsText);
				window.draw(DeathLimitText);
				window.draw(AliveInputText);
				window.draw(BirthInputText);
				window.draw(IterationsInputText);
				window.draw(DeathText);

				window.draw(inputText);

				window.draw(caMap);
			}
			else if (bspActive)
			{
				window.draw(bspMap);
			}
		}
		window.display();
	}

	return 0;
}

void DoCA()
{

}

void DoBSP()
{

}