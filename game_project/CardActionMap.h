#pragma once
#include "CardsInDeck.h"
#include "ActionPoint.h"
#include "Point.h"
#include "standaloneFunctions.h"

//Class that stores information about all the card actions occuring on the map and can pass
//their locations to the tileMap to update the tiles accordingly
class CardActionMap
{
public:
	CardActionMap();

	void reset();

	void newAction(int cardIndex, CardsInDeck cardsInDeck, int direction, int playerXPos, int playerYPos, std::vector<std::vector<int>> collision);

	void action(float frameTime);

	std::vector<ActionPoint> cardActionMap;

private:
	bool lineOfSightObstructed(int playerXPos, int playerYPos, int xPos, int yPos, std::vector<std::vector<int>> collision);
};

