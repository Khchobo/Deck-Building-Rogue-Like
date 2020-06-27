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
#include "Enemy.h"

class Game
{
public:

	sf::RenderStates renderState;
	TileMap tileMap;
	int mapWidth, mapHeight;

	WindowInfo windowInfo;

	sf::RenderWindow window;

	Game(int windowedWidth, int windowedHeight, std::map<std::string, BattlingCharacterType>& battlingCharacterTypes,Json::Value gameData,ImageManager& imageManager) :

		imageManager(imageManager),
		player(windowInfo, &battlingCharacterTypes["player"], "player", imageManager),
		battlingCharacterTypes(battlingCharacterTypes),
		gameData(gameData)
	{
		/////////////
		//LOAD DATA//
		/////////////
		
		windowInfo.fullscreen = gameData["fullscreen"].asBool();

		//////////////
		//CREATE MAP//
		//////////////

		if (gameData["debugSettings"]["loadTestMap"].asBool())
		{
			loadTestMap();
		}
		else
		{
			//TODO GENERATING MAPS
		}
	
		if (gameData["debugSettings"]["testEnemy"].asBool())
		{
			Enemy newEnemy(&battlingCharacterTypes["basicSlime"], "basicSlime", sf::Vector2i(13, 13), windowInfo,imageManager);
			enemies.push_back(newEnemy);
		}

		fixedColourShader.loadFromFile("assets/fixedColourShader.frag", sf::Shader::Fragment);
		
		windowInfo.setWindowedWidth(windowedWidth);
		windowInfo.setWindowedHeight(windowedHeight);

		//create window of appropriate size depending on default fullscreen setting
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
	Player player;
	Json::Value gameData;

	//Determines which mode we are in. 0 is overworld movement, 1 is card fight.
	int renderMode;
	int renderModeTimeout = 0;

	//default minimum distance between the player and edge of the screen
	//todo fix bug where it doesnt adjest with gui and fullscreen
	float playerDistanceFromEdgeX = 200, playerDistanceFromEdgeY = 200;

	void draw();	
	void action();	
	void initialise();
	/**
	*Create a new window at the new size and move objects in window accordingly. Currently is only used to toggle windowed and fullscreen
	*/
	void resize();
	void resizeActiveScene();
	void initialiseBattleMode();
	void loadTestMap();

	ImageManager imageManager;

	std::vector<Enemy> enemies;

	std::vector<std::vector<int>> collisionMap;
	std::vector<TileType> tileTypeMap;

};