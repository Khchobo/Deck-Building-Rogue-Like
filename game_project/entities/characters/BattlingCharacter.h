#pragma once

#include "standaloneFunctions.h"
#include "cardsInHand.h"
#include "CardsInDeck.h"
#include "BattlingCharacterType.h"
#include "CardActionMap.h"
#include <memory>

using namespace standaloneFunctions;

enum class actionState { idle,move,attack,death };
enum class iFrameState {invincible, vunerable};

class BattlingCharacter : public PositionalEntity
{
public:

	BattlingCharacter(BattlingCharacterType* type, std::string identity, ImageManager* imageManager, sf::Vector2f pos);
	
	//Todo use this
	void Initialise() override { return; };
	void Update() override { return; };

	void InitiateNewMotion(unsigned int direction, std::vector<std::vector<int>>& collision);
	virtual void InitialiseBattleMode();
	virtual void DrawToScreen(sf::RenderWindow& window);
	actionState GetActionState();
	int GetDirection();
	void SetDirection(int direction);

	//current tile alignment or tile alignment before current motion began
	sf::Vector2i m_currentTilePos;

	CardsInHand m_cardsInHand;
	CardsInDeck m_cardsInDeck;

	BattlingCharacterType* m_battlingCharacterType;
	
	float m_yPosNoOffset;

	float m_cardPoints;
	float m_health;

	std::map<BehaviourTrigger, bool> m_behaviourTriggers = { {useCard,false}, {drawCardFromDeck,false },
														{initiateMotion, false}, {selectCardLeft, false},
														{selectCardRight, false},{directionChange,false},
														{destroySelf,false},{takeDamage,false},{endMotion,false},
														{triggerDeath,false},{defaultAnimation,false},{useCardSuccess,false} }; //TODO really need to write a script to do this

protected:

	void UpdateMotion();
	void UpdateDamageAndHealth(CardActionMap cardActionMap);
	void Update(std::vector<std::vector<int>>& collision, int renderMode, int direction, CardActionMap cardActionMap);
	//set all behaviour triggers to false each frame
	void ResetBehaviourTriggers();
	void ArrowDirectionUpdate();

	actionState m_actionState = actionState::idle;
	iFrameState m_iFrameState = iFrameState::vunerable;

	//direction character is facing, 0 is up and then proceed counter clockwise
	int m_direction;
	float m_verticalHopOffset;
	sf::Vector2i m_futureTilePos;
	//Todo switch this to a sf::vector2f
	float m_distanceMovedX;
	float m_distanceMovedY;

	//TODO make data
//card point cost to move 1 tile
	float m_cardPointsStepCost;

	PositionalEntity m_directionalArrow;

	//for discrete motion, determines whether a motion animation is already occurring
	bool m_bInMotion = false;
	//how far the motion the character is, 0 in beginning and 1 is end.
	float m_motionPercentage;
	

};

