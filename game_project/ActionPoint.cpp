#include "ActionPoint.h"



ActionPoint::ActionPoint(int xPos, int yPos, float activationTime, float destructionTime, AttackElement attackElement) :
	xPos(xPos), yPos(yPos), activationTime(activationTime), destructionTime(destructionTime), attackElement(attackElement)
{
	aliveTime = 0.0;
	active = false;
}

