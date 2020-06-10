#include "CardAction.h"



CardAction::CardAction(int xPos, int yPos, float activationTime, float destructionTime, AttackElement attackElement, float attackDamage) :
	xPos(xPos), yPos(yPos), activationTime(activationTime), destructionTime(destructionTime), attackElement(attackElement), attackDamage(attackDamage)
{
	aliveTime = 0.0;
	active = false;
}

