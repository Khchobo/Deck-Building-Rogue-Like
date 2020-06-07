#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <assert.h>
#include "json\json.h"
#include "standaloneFunctions.h"


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


	// AI TRAITS
	float movementTimeoutIdle;
	float cardPointConservation;
	int attackVisionRadius;
	float movementTimeoutRunning;
	Dir targetDirection;
	int targetDistance;
	float maxHealth;

};

