#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <assert.h>
#include "json\json.h"
#include "standaloneFunctions.h"
#include "StateAnimation.h"
#include "SquashAnimation.h"
#include <unordered_map>
#include "TransitionMap.h"
#include "Distributions.h"

using namespace standaloneFunctions;

enum class Dir { Front, Left, Right, Back };

class BattlingCharacterType
{
public:

	BattlingCharacterType();

	BattlingCharacterType(std::string typeName);

	float cardPointsMax, cardPointRecoveryRate;
	//how long tile motion takes for tile based motion
	float motionTime;
	std::string identifier;

	//maps the title of each animation onto its animation class instance
	std::unordered_map<std::string, std::shared_ptr<StateAnimation>> animationMap;
	TransitionMap animationTransitions;
	// AI TRAITS
	float movementTimeoutChase;
	float cardPointConservation;
	int attackVisionRadius;
	float movementTimeoutFlee;
	Dir targetDirection;
	int targetDistance;
	float maxHealth;
	CharType characterType;

	//card information
	unsigned int deckSize;
	int maxHandSize;
	ExplicitDiscreteDist cardTypeDistribution;
	std::unordered_map<std::string, CardDists> cardDistributions;

private:
	void assignTransitionDataToMap(Json::Value data, std::unordered_map<std::string, BehaviourTrigger>& triggerMap);
	void loadAnimationData(std::string typeName);
	void loadCardDistributions(Json::Value data);
};

