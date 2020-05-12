#pragma once
#include "Card.h"
class ActionPoint
{
public:
	ActionPoint(int xPos, int yPos, float activationTime, float destructionTime, AttackElement attackElement);

	//map position in tiles
	int xPos;
	int yPos;

	//how long this point has been alive
	float aliveTime;

	//time at which this action point switches on, and then destructs
	float activationTime;
	float destructionTime;

	//whether the point is switched on
	bool active;

	AttackElement attackElement;

	//TODO damage info, attack type, etc?
};

