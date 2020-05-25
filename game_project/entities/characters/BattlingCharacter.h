#pragma once
#include "entities\other\Entity.h"
#include "standaloneFunctions.h"
#include "cardsInHand.h"
#include "CardsInDeck.h"
#include "BattlingCharacterType.h"

using namespace standaloneFunctions;

class BattlingCharacter : public Entity
{
public:

	BattlingCharacter(BattlingCharacterType* type,std::string identity);

	float cardPoints;

	void initiateNewMotion(unsigned int direction, std::vector<std::vector<int>>& collision);

	virtual void initialiseBattleMode();

	//current tile alignment or tile alignment before current motion began
	int currentXTilePos;
	int currentYTilePos;

	CardsInHand cardsInHand;
	CardsInDeck cardsInDeck;

	BattlingCharacterType* type;
	
	float yPosNoOffset;

protected:

	std::map<BehaviourTrigger, bool> behaviourTriggers = { {useCard,false}, {drawCardFromDeck,false },
															{initiateMotion, false}, {selectCardLeft, false},
															{selectCardRight, false} };

	float verticalHopOffset;

	void updateMotion(WindowInfo windowInfo);
	virtual void checkForMotion();

	//TODO make data
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
	

};

