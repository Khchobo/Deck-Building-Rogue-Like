#pragma once

#include "Entity.h"
#include "Sprite.h"
#include "standaloneFunctions.h"

class CardSprite : public PositionalEntity
{
public:

	//whether the card is currently undergoing an animation. 
	//if so, the position variable tracks which direction
	//it should be moving in
	bool inMotion;

	float offset = 0;

	//0 is not selected, 1 is selected. Only switches once the in motion
	//variable is set to false, so for example if inMotion is true and 
	//position is set to 0, we know the card is currently moving upwards
	int movementLocation;

	//the ID of the card in the deck
	long double id;

	CardSprite() {}

	CardSprite(PositionalEntity* deckSprite, ImageManager* imageManager) : PositionalEntity("cardSprite", deckSprite->position, imageManager, "card2", this, 1)
	{
		movementLocation = 2;
		inMotion = 1;
		previousPos = position;
	}

	void move(int i);


	//the location before this motion was initiated
	sf::Vector2f previousPos;

private:

	//how long tile motion takes for tile based motion
	float motionTime;

	//how far the motion the player is, 0 in beginning and 1 is end.
	float motionPercentage = 0;

	//the difference in motion percentage between the last frame and this one
	float motionDifference = 0;
	
};
