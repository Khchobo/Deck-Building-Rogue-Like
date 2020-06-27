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

#include "standaloneFunctions.h"

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

private:
	/**
	*Parses the transistion data stored in 'data' and stores in in animationTransitions
	*@param data animation transistion data to store in animationTransitions
	*@param triggerMap the map that associates the behaviour triggers stored as strings in the json file with their equivalent enums
	*/
	void assignTransitionDataToMap(Json::Value data, std::unordered_map<std::string, BehaviourTrigger>& triggerMap);
	void loadAnimationData(std::string typeName);
};

