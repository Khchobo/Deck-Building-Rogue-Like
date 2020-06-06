#include "BattlingCharacter.h"


BattlingCharacter::BattlingCharacter(BattlingCharacterType* type,std::string identity) : 
	cardsInHand(1), cardsInDeck(50), type(type) 
{
	type->identifier = identity;
	cardPoints = type->cardPointsMax;
	cardPointsStepCost = 5;
};

void BattlingCharacter::checkForMotion() {}

void BattlingCharacter::updateMotion(WindowInfo windowInfo)
{
	//once motion is completed, end in motion state and change tile alignement 
	if (motionPercentage == 1)
	{
		inMotion = 0;
		currentXTilePos = futureXTilePos;
		currentYTilePos = futureYTilePos;
	}

	//motion percentage determined according to frame time to keep motion speed constant regardless of framerate
	motionPercentage += frameTime / type->motionTime;

	//cap the percentage at 1
	if (motionPercentage > 1)
	{
		motionPercentage = 1;
	}

	float newXPos;
	float newYPos;


	newXPos = (currentXTilePos + standaloneFunctions::easeInOut(motionPercentage) * (futureXTilePos - currentXTilePos))*windowInfo.tileSizeInPixels;
	newYPos = (currentYTilePos + standaloneFunctions::easeInOut(motionPercentage) * (futureYTilePos - currentYTilePos))*windowInfo.tileSizeInPixels;

	verticalHopOffset = quadraticHop(50, motionPercentage);
	
	//the difference between the location on this frame and the previous frame
	distanceMovedX = newXPos - xPos;
	distanceMovedY = newYPos - yPosNoOffset;

	//update the location as a linear interpolation between the old location and new, weighted by motion percentage
	xPos = newXPos;
	yPosNoOffset = newYPos;
	yPos = newYPos-verticalHopOffset;
}

void BattlingCharacter::initialiseBattleMode()
{
}

void BattlingCharacter::action(std::vector<std::vector<int>>& collision, WindowInfo windowInfo, int renderMode, int direction)
{
	
	//PLAYER MOTION
	if (behaviourTriggers[initiateMotion] && cardPoints > cardPointsStepCost && !(inMotion))
	{
		std::cout << direction << std::endl;
		initiateNewMotion(direction, collision);
	}

	if (inMotion == 1)
	{
		updateMotion(windowInfo);
	}


	
}

void BattlingCharacter::resetBehaviourTriggers()
{
	std::map<BehaviourTrigger, bool>::iterator it;
	for (it = behaviourTriggers.begin(); it != behaviourTriggers.end(); it++)
	{
		behaviourTriggers[it->first] = false;
	}
}

void BattlingCharacter::initiateNewMotion(unsigned int direction, std::vector<std::vector<int>>& collision)
{
	switch (direction) {
		//up
	case(0):
		futureXTilePos = currentXTilePos;
		futureYTilePos = currentYTilePos - 1;
		break;
		//left
	case(1):
		futureXTilePos = currentXTilePos - 1;
		futureYTilePos = currentYTilePos;
		break;
		//down
	case(2):
		futureXTilePos = currentXTilePos;
		futureYTilePos = currentYTilePos + 1;
		break;
		//right
	case(3):
		futureXTilePos = currentXTilePos + 1;
		futureYTilePos = currentYTilePos;
		break;
	}
	if (collision[futureYTilePos][futureXTilePos] == 0)
	{
		cardPoints -= cardPointsStepCost;
		inMotion = true;
		motionPercentage = 0.0;
	}
}
