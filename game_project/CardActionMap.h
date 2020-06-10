#pragma once
#include "CardsInDeck.h"
#include "CardAction.h"
#include "standaloneFunctions.h"

//Class that stores information about all the card actions occuring on the map and can pass
//their locations to the tileMap to update the tiles accordingly
class CardActionMap
{
public:
	CardActionMap();

	void reset();

	void newAction(int cardIndex, CardsInDeck cardsInDeck, int direction, sf::Vector2i playerPos, std::vector<std::vector<int>> collision);

	void updateAllCardActions(float frameTime);

	std::vector<CardAction> cardActionMap;

private:
	bool lineOfSightObstructed(int playerXPos, int playerYPos, int xPos, int yPos, std::vector<std::vector<int>> collision);
};

