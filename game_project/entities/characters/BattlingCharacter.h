#pragma once
#include "entities\other\Entity.h"
#include "standaloneFunctions.h"
#include "cardsInHand.h"
#include "CardsInDeck.h"
#include "BattlingCharacterType.h"
#include "CardActionMap.h"

using namespace standaloneFunctions;

enum class actionState { idle,move,attack };
enum class iFrameState {invincible, vunerable};

class BattlingCharacter : public Entity
{
public:

	BattlingCharacter(BattlingCharacterType* type,std::string identity,ImageManager& imageManager);

	float cardPoints;
	float health;

	void initiateNewMotion(unsigned int direction, std::vector<std::vector<int>>& collision);

	virtual void initialiseBattleMode();
	void draw(sf::RenderWindow& window, Point backgroundTexturePosition, ImageManager& imageManager);

	//current tile alignment or tile alignment before current motion began
	sf::Vector2i currentTilePos;

	CardsInHand cardsInHand;
	CardsInDeck cardsInDeck;

	BattlingCharacterType* type;
	
	float yPosNoOffset;

protected:

	std::map<BehaviourTrigger, bool> behaviourTriggers = { {useCard,false}, {drawCardFromDeck,false },
															{initiateMotion, false}, {selectCardLeft, false},
															{selectCardRight, false},{directionChange,false} };
	actionState state=actionState::idle;


	//direction character is facing, 0 is up and then proceed counter clockwise
	int direction;
	float verticalHopOffset;
	sf::Vector2i futureTilePos;
	//Todo switch this to a sf::vector2f
	float distanceMovedX;
	float distanceMovedY;

	void updateMotion(WindowInfo windowInfo);

	//TODO unsure what this is here for, may remove it later
	virtual void checkForMotion();

	void action(std::vector<std::vector<int>>& collision,WindowInfo windowInfo, int renderMode, int direction);
	//set all behaviour triggers to false each frame
	void resetBehaviourTriggers();

	//TODO make data
	//card point cost to move 1 tile
	float cardPointsStepCost;

	Entity directionalArrow;
	void arrowDirectionUpdate();
	sf::Vector2i directionalArrowOffset;

	//for discrete motion, determines whether a motion animation is already occurring
	bool inMotion = false;
	//how far the motion the character is, 0 in beginning and 1 is end.
	float motionPercentage;
	

};

