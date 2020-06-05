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

	Game(int windowedWidth, int windowedHeight, std::map<std::string, BattlingCharacterType> battlingCharacterTypes,Json::Value gameData) :

		player(windowInfo, &battlingCharacterTypes["player"], "player"),
		battlingCharacterTypes(battlingCharacterTypes),
		testEnemy(&battlingCharacterTypes["basicSlime"], "basicSlime",14,14, windowInfo),gameData(gameData)
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
	

		//iterate over each enemy and load its data from the folder into the BattlingCharacterType object
		for (auto& p : std::filesystem::directory_iterator("assets/data/characters"))
		{
			std::string fileName = p.path().u8string().erase(0, 23);
			fileName.erase(fileName.end()-9, fileName.end());

			std::cout << fileName << std::endl;

			if (fileName == "player") continue;

			battlingCharacterTypes.insert(std::pair<std::string, BattlingCharacterType>(fileName, BattlingCharacterType(fileName)));
			
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
	void resize();
	void resizeActiveScene();
	void initialiseBattleMode();
	Json::Value loadGameData();
	void loadTestMap();

	Enemy testEnemy;

	std::vector<std::vector<int>> collisionMap;
	std::vector<TileType> tileTypeMap;
	std::vector<std::vector<int>> activePlayerActionPoints;

	
};