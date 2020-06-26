#pragma once
#include "Card.h"
#include "standaloneFunctions.h"

using namespace standaloneFunctions;

/**
*A point on the TileMap where an attack can appear at some point after being constructed
*
*When an attack takes place, depending on the attack an array of attack points are
*generated. Each of these action points becomes active after a preset time depending
*on the distance from the attack user (exact implementation in CardActionMap and the attack speed.
*The action point also has a destructionTime, once it reaches this time while it is active it will
*self destruct.
*/
class CardAction
{
public:
	CardAction(int xPos, int yPos, float activationTime, float destructionTime, AttackElement attackElement,float attackDamage, CharType characterTypek);
	//test
	//map position in tiles
	int xPos;
	int yPos;

	//how long this point has been alive
	float aliveTime;

	//time at which this action point switches on, and then destructs
	float activationTime;
	float destructionTime;

	CharType characterType;

	//whether the point is switched on
	bool active;

	AttackElement attackElement;
	float attackDamage;

	//TODO damage info, attack type, etc?
};

