#pragma once

#include "Entity.h"
#include "Sprite.h"
#include "standaloneFunctions.h"

class CardSprite : public PositionalEntity
{
public:

	enum CardLocationState { New, BecomingSelected, BecomingUnselected, Unselected, Selected, BelowUsedBecomingSelected, BelowUsedNotBecomingSelected };

	//whether the card is currently undergoing an animation. 
	//if so, the position variable tracks which direction
	//it should be moving in
	bool inMotion;

	float offset = 0;

	//the ID of the card in the deck
	long double id;

	CardSprite(PositionalEntity* deckSprite, ImageManager* imageManager, Entity* parent) : PositionalEntity("cardSprite", deckSprite->position, imageManager, "card2", parent, parent, 1)
	{
		SetState(CardLocationState::New);
	}

	void UpdateCardMotion(int index);
	void SetState(CardLocationState state);
	CardLocationState GetState();

	//the location before this motion was initiated
	sf::Vector2f previousPos;

private:



	//0 is not selected, 1 is selected. Only switches once the in motion
	//variable is set to false, so for example if inMotion is true and 
	//position is set to 0, we know the card is currently moving upwards
	CardLocationState locationState;

	//how long tile motion takes for tile based motion
	float motionTime;

	//how far the motion the player is, 0 in beginning and 1 is end.
	float motionPercentage = 0;

	//the difference in motion percentage between the last frame and this one
	float motionDifference = 0;
	
};
