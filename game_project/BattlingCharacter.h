#pragma once
#include "Entity.h"
#include "standaloneFunctions.h"
#include "cardsInHand.h"
#include "CardsInDeck.h"

using namespace standaloneFunctions;

class BattlingCharacter : public Entity
{
public:
	BattlingCharacter();

	float cardPoints, cardPointsMax, cardPointRecoveryRate; //in points per second

	void initiateNewMotion(unsigned int direction, std::vector<std::vector<int>>& collision);

	virtual void initialiseBattleMode();

	//current tile alignment or tile alignment before current motion began
	int currentXTilePos;
	int currentYTilePos;

	CardsInHand cardsInHand;
	CardsInDeck cardsInDeck;

protected:

	float verticalHopOffset;

	void updateMotion(WindowInfo windowInfo);
	virtual void checkForMotion();

	//card point cost to move 1 tile
	float cardPointsStepCost;

	int futureXTilePos;
	int futureYTilePos;

	float distanceMovedX;
	float distanceMovedY;

	//for discrete motion, determines whether a motion animation is already occurring
	bool inMotion = false;
	//how far the motion the character is, 0 in beginning and 1 is end.
	float motionPercentage;
	//how long tile motion takes for tile based motion
	float motionTime = 0.15;

};

