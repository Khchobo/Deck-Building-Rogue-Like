#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include <thread>
#include <assert.h>
#include <time.h>
#include "CardsInHand.h"
#include "WindowInfo.h"
#include "entities\other\NumberEntity.h"
#include "BattlingCharacter.h"
#include "globalVariables.h"
#include "BattlingCharacterType.h"
#include "standaloneFunctions.h"
#include "CardActionMap.h"

using namespace std;

class Player : public BattlingCharacter
{
public:

	Player(WindowInfo windowInfo, BattlingCharacterType& type) : BattlingCharacter(type), cardsInHand(1), cardsInDeck(50)
	{
		texture.loadFromFile("assets/tic_tac.png");

		cardPoints = 50;
		cardPointsStepCost = 5;
		
		currentXTilePos = 2;
		currentYTilePos = 2;

		xPos = currentXTilePos * windowInfo.tileSizeInPixels;
		yPos = currentYTilePos * windowInfo.tileSizeInPixels;

	}

	CardsInHand cardsInHand;
	CardsInDeck cardsInDeck;

	void action(std::map<int, bool> keyboardArray, float& playerDistanceFromEdgeX, float& playerDistanceFromEdgeY,
		std::vector<std::vector<int>>& collision, WindowInfo windowInfo, int renderMode, CardActionMap& cardActionMap);

	bool checkForMotion(std::map<int, bool> keyboardArray);

	void resize(WindowInfo windowInfo);

	void draw(sf::RenderWindow& window, float backgroundXPos, float backgroundYPos);

	//direction player is facing, 0 is up and then proceed counter clockwise
	int direction;

	//This is the entity that displays the number of card points to the window. cardPoints stores the actual value
	NumberEntity cardPointsNumber;

};