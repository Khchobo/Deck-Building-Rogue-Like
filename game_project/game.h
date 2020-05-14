#include "SFML/Graphics.hpp"
#include <vector>
#include <math.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include <assert.h>
#include <time.h>
#include "player.h"
#include "TileMap.h"
#include "CardsInDeck.h"
#include "WindowInfo.h"
#include "cardActionMap.h"


class Game
{
public:

	sf::RenderStates renderState;
	TileMap tileMap;
	int mapWidth, mapHeight;

	//size of the screen in windowed mode
	int windowedWidth, windowedHeight;

	//current screen size (changes when in fullscreen)
	int windowWidth, windowHeight;

	unsigned int tileSize = 16;
	std::vector<std::vector<int>> collision;
	sf::RenderWindow window;
	unsigned int pixelSize = 2;



	Game(int windowedWidth, int windowedHeight, std::vector<TileType> gameMapInfo, int mapXSize, int mapYSize, std::vector<std::vector<int>> collision) :
		tileMap(mapXSize, mapYSize, 16, gameMapInfo), player(pixelSize, tileSize), mapWidth(mapXSize), mapHeight(mapYSize),
		windowedWidth(windowedWidth), windowedHeight(windowedHeight), collision(collision), cardsInHand(1), cardsInDeck(50)
	{
		sf::ContextSettings settings;
		settings.antialiasingLevel = 8;

		fixedColourShader.loadFromFile("assets/fixedColourShader.frag", sf::Shader::Fragment);

		window.create(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "SFMLtest", sf::Style::Fullscreen);
		fullscreen = 1;
		//window.setFramerateLimit(30);
		window.setVerticalSyncEnabled(true);
	}

	void loop();
	
private:

	CardsInHand cardsInHand;
	CardsInDeck cardsInDeck;
	CardActionMap cardActionMap;

	std::map<int,bool> keyboardArray;

	sf::Clock clock;
	sf::Shader fixedColourShader;

	//Determines which mode we are in. 0 is overworld movement, 1 is card fight.
	int renderMode;

	//How much to change the window size by in tiles if renderMode 1 is on
	int tileReductionX;
	int tileReductionY;

	Player player;

	//TODO boolify
	int fullscreen = 0;

	//TODO rename
	int renderModeTimeout = 0;

	WindowInfo windowInfo;

	//TODO refactor??
	//player distance from top and left edge
	float playerDistanceFromEdgeX = 80, playerDistanceFromEdgeY = 80;

	void draw();	
	void action();	
	void initialise();
	void resize();
	void resizeVisibleField();
	void initialiseBattleMode();

};