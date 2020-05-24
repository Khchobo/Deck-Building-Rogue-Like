#pragma once
#include "Card.h"

/**
*A point on the TileMap where an attack can appear at some point after being constructed
*
*When an attack takes place, depending on the attack an array of attack points are
*generated. Each of these action points becomes active after a preset time depending
*on the distance from the attack user (exact implementation in CardActionMap and the attack speed.
*The action point also has a destructionTime, once it reaches this time while it is active it will
*self destruct. TODO currently there is no implementation for BattlingCharacters to take damage
*when touching an active action point
*/
class ActionPoint
{
public:
	ActionPoint(int xPos, int yPos, float activationTime, float destructionTime, AttackElement attackElement);
	//test
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

