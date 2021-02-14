#pragma once

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
#include "cardActionMap.h"
#include "globalVariables.h"
#include "BattlingCharacterType.h"
#include <filesystem>
#include "Enemy.h"

class Game
{
public:

	sf::RenderStates renderState;
	TileMap tileMap;
	int mapWidth, mapHeight;
	sf::Vector2f backgroundTexturePosition;
	sf::RenderWindow window;

	Game(int windowedWidth, int windowedHeight, std::map<std::string, BattlingCharacterType>& battlingCharacterTypes,Json::Value gameData,ImageManager* imageManager) :

		imageManager(imageManager),
		player(&battlingCharacterTypes["player"], "player", imageManager),
		battlingCharacterTypes(battlingCharacterTypes),
		gameData(gameData)
	{
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
			for (int i = 0; i < 1; i++)
			{
				
				enemies.emplace_back(std::make_unique<Enemy>(&battlingCharacterTypes["basicSlime"], "basicSlime", sf::Vector2i(13 + i, 13 + i), imageManager));
			}
		}

		//fixedColourShader.loadFromFile("assets/fixedColourShader.frag", sf::Shader::Fragment);

		//create window of appropriate size depending on default fullscreen setting
		window.create(sf::VideoMode(windowInfo.getWindowWidth(), windowInfo.getWindowHeight()), "Game", windowInfo.fullscreen==1 ? sf::Style::Fullscreen : sf::Style::Default);

		//TODO
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

	void setBackgroundTexturePosition();
	void draw();	
	void action();	
	void initialise();
	void resize();
	void resizeActiveScene();
	void initialiseBattleMode();
	void loadTestMap();

	ImageManager* imageManager;

	std::vector<std::unique_ptr<Enemy>> enemies;

	std::vector<std::vector<int>> collisionMap;
	std::vector<TileType> tileTypeMap;

};