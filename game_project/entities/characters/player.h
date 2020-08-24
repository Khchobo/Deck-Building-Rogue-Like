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

class Player : public BattlingCharacter
{
public:

	Player(WindowInfo windowInfo, BattlingCharacterType* type, std::string identity,ImageManager& imageManager) : BattlingCharacter(type, identity, imageManager)
	{
		currentTilePos = sf::Vector2i(2, 2);
		position = sf::Vector2f(static_cast<float>(currentTilePos.x * windowInfo.tileSizeInPixels), static_cast<float>(currentTilePos.y * windowInfo.tileSizeInPixels));
		initialise("tic_tac.png", position, imageManager);
	}

	void action(std::map<int, bool> keyboardArray, float& playerDistanceFromEdgeX, float& playerDistanceFromEdgeY,
		std::vector<std::vector<int>>& collision, WindowInfo windowInfo, int renderMode, CardActionMap& cardActionMap, ImageManager& imageManager);

	void checkInputs(std::map<int, bool> keyboardArray);

	void resize(WindowInfo windowInfo);

	//This is the entity that displays the number of card points to the window. cardPoints stores the actual value
	NumberEntity cardPointsNumber;
	NumberEntity healthNumber;
};