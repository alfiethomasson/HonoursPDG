#include <iostream>
#include "Grid.h"
#include "Generator.h"
#include <random>
#include <SFML/Graphics.hpp>

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
	title.setCharacterSize(30);
	DrunkardWalkText.setCharacterSize(30);
	BSPText.setCharacterSize(30);
	title.setFillColor(sf::Color::White);
	DrunkardWalkText.setFillColor(sf::Color::White);
	BSPText.setFillColor(sf::Color::White);

	title.setPosition(200.0f, 0.0f);
	DrunkardWalkText.setPosition(200.0f, 200.0f);
	BSPText.setPosition(200.0f, 300.0f);

	bool bspActive = false;
	bool drunkardwalkActive = false;

	sf::View mainView(sf::FloatRect(0.f, 0.f, 800.f, 600.f));

	window.setView(mainView);
	float curZoom = 1.f;

	sf::String methodName = "Test";
	Generator *gen = new Generator(methodName, 1000, 1000);
	sf::Image output;
	output = gen->GenerateDungeon(100);
	output = gen->GenerateBSP();
	sf::Texture imgText;
	imgText.loadFromImage(output);

	sf::Sprite dungeon;
	dungeon.setTexture(imgText);

	dungeon.setPosition(0, 0);

	while (window.isOpen())
	{
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
		}

		if (inMenu)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
			{
				output = gen->GenerateDungeon(1000000);
				imgText.loadFromImage(output);
				dungeon.setTexture(imgText);

				inMenu = false;
				drunkardwalkActive = true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
			{
				output = gen->GenerateBSP();
				imgText.loadFromImage(output);
				dungeon.setTexture(imgText);

				inMenu = false;
				bspActive = true;
			}
			window.clear();

			window.draw(title);
			window.draw(DrunkardWalkText);
			window.draw(BSPText);

		}
		else
		{
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
				window.draw(dungeon);
			}
			else if (bspActive)
			{
				window.draw(dungeon);
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