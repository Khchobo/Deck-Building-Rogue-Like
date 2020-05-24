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
#include "entities\characters\player.h"
#include "TileMap.h"
#include "CardsInDeck.h"
#include "WindowInfo.h"
#include "cardActionMap.h"
#include "BattlingCharacterType.h"
#include <filesystem>

class Game
{
public:

	sf::RenderStates renderState;
	TileMap tileMap;
	int mapWidth, mapHeight;

	WindowInfo windowInfo;

	std::vector<std::vector<int>> collision;
	sf::RenderWindow window;

	Game(int windowedWidth, int windowedHeight, std::vector<TileType> gameMapInfo, int mapXSize, int mapYSize,
		std::vector<std::vector<int>> collision, std::map<std::string, BattlingCharacterType> battlingCharacterTypes) :

		tileMap(mapXSize, mapYSize, 16, gameMapInfo,collision), player(windowInfo, &battlingCharacterTypes["player"]), mapWidth(mapXSize),
		mapHeight(mapYSize), collision(collision),battlingCharacterTypes(battlingCharacterTypes),
		activePlayerActionsPoints(collision.size(), std::vector<int>(collision[0].size)) //initialise a matrix of zeroes the same size as the collision map
	{
		sf::ContextSettings settings;
		settings.antialiasingLevel = 8;

		//iterate over each enemy and load its data from the folder into the BattlingCharacterType object
		for (auto& p : std::filesystem::directory_iterator("assets/data/characters"))
		{
			std::string folderName = p.path().u8string().erase(0, 23);
			if (folderName == "player") continue;
			battlingCharacterTypes.insert(std::pair<std::string, BattlingCharacterType>(folderName, BattlingCharacterType(folderName)));
			std::cout << battlingCharacterTypes[folderName].cardPointRecoveryRate;
		}

		fixedColourShader.loadFromFile("assets/fixedColourShader.frag", sf::Shader::Fragment);

		std::cout << windowInfo.fullscreen;
		
		windowInfo.setWindowedWidth(windowedWidth);
		windowInfo.setWindowedHeight(windowedHeight);

		switch (windowInfo.fullscreen) {
		case(0):
			window.create(sf::VideoMode(windowInfo.windowedWidthPixels, windowInfo.windowedHeightPixels), "Game", sf::Style::Default);
			break;
		case(1):
			window.create(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Game", sf::Style::Fullscreen);
			break;
		}

		//window.setFramerateLimit(30);
		window.setVerticalSyncEnabled(true);
	}

	void loop();
	
private:

	CardActionMap cardActionMap;

	std::map<std::string, BattlingCharacterType> battlingCharacterTypes;

	std::map<int,bool> keyboardArray;

	sf::Clock clock;
	sf::Shader fixedColourShader;

	//Determines which mode we are in. 0 is overworld movement, 1 is card fight.
	int renderMode;

	Player player;

	//TODO rename
	int renderModeTimeout = 0;

	//TODO refactor??
	//player distance from top and left edge
	float playerDistanceFromEdgeX = 80, playerDistanceFromEdgeY = 80;

	void draw();	
	void action();	
	void initialise();
	void resize();
	void resizeActiveScene();
	void initialiseBattleMode();

	std::vector<std::vector<int>> activePlayerActionsPoints;
};