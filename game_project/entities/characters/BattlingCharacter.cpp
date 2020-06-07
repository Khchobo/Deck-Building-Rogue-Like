#include "BattlingCharacter.h"


BattlingCharacter::BattlingCharacter(BattlingCharacterType* type,std::string identity,ImageManager& imageManager) :
	cardsInHand(), cardsInDeck(), type(type) 
{
	type->identifier = identity;
	cardPoints = type->cardPointsMax;
	cardPointsStepCost = 5;
	directionalArrow.initialise("directionalArrow.png", position, 0, imageManager);
};

void BattlingCharacter::checkForMotion() {}

void BattlingCharacter::updateMotion(WindowInfo windowInfo)
{
	//once motion is completed, end in motion state and change tile alignement 
	if (motionPercentage == 1)
	{
		inMotion = 0;
		currentTilePos = futureTilePos;
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


	newXPos = (currentTilePos.x + standaloneFunctions::easeInOut(motionPercentage) * (futureTilePos.x - currentTilePos.x))*windowInfo.tileSizeInPixels;
	newYPos = (currentTilePos.y + standaloneFunctions::easeInOut(motionPercentage) * (futureTilePos.y - currentTilePos.y))*windowInfo.tileSizeInPixels;

	verticalHopOffset = quadraticHop(50, motionPercentage);
	
	//the difference between the location on this frame and the previous frame
	distanceMovedX = newXPos - position.x;
	distanceMovedY = newYPos - yPosNoOffset;

	//update the location as a linear interpolation between the old location and new, weighted by motion percentage
	position.x = newXPos;
	yPosNoOffset = newYPos;
	position.y = newYPos-verticalHopOffset;
}

void BattlingCharacter::initialiseBattleMode()
{
}

void BattlingCharacter::action(std::vector<std::vector<int>>& collision, WindowInfo windowInfo, int renderMode, int direction)
{
	//////////
	//MOTION//
	//////////

	if (behaviourTriggers[initiateMotion] && cardPoints > cardPointsStepCost && !(inMotion))
	{
		initiateNewMotion(direction, collision);
	}

	if (inMotion == 1)
	{
		updateMotion(windowInfo);
	}

	sf::Vector2i directionalArrowOffset;
	int directionalArrowRotation;
	switch (direction)
	{
	case(0):
		directionalArrowOffset = sf::Vector2i(0, -32);
		directionalArrowRotation = 0;
		break;
	case(1):
		directionalArrowOffset = sf::Vector2i(-32, 0);
		directionalArrowRotation = 270;
		break;
	case(2):
		directionalArrowOffset = sf::Vector2i(0, 32);
		directionalArrowRotation = 180;
		break;
	case(3):
		directionalArrowOffset = sf::Vector2i(32, 0);
		directionalArrowRotation = 90;
		break;
	default:
		throw std::invalid_argument("Direction cannot take value" + std::to_string(direction));
	}

	directionalArrow.position =sf::Vector2f( position.x+directionalArrowOffset.x+16,position.y + directionalArrowOffset.y + 16);
	directionalArrow.sprite.setRotation(directionalArrowRotation);

	cardPoints = min(static_cast<float>(type->cardPointsMax), cardPoints + type->cardPointRecoveryRate*frameTime);
	
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
		futureTilePos = sf::Vector2i(currentTilePos.x, currentTilePos.y-1);
		break;
		//left
	case(1):
		futureTilePos = sf::Vector2i(currentTilePos.x-1, currentTilePos.y);
		break;
		//down
	case(2):
		futureTilePos = sf::Vector2i(currentTilePos.x, currentTilePos.y +1);
		break;
		//right
	case(3):
		futureTilePos = sf::Vector2i(currentTilePos.x+1, currentTilePos.y);
		break;
	}
	if (collision[futureTilePos.y][futureTilePos.x] == 0)
	{
		cardPoints -= cardPointsStepCost;
		inMotion = true;
		motionPercentage = 0.0;
	}
}

void BattlingCharacter::draw(sf::RenderWindow& window, Point backgroundTexturePosition, ImageManager& imageManager)
{
	directionalArrow.position.x += backgroundTexturePosition.x;
	directionalArrow.position.y += backgroundTexturePosition.y;
	directionalArrow.draw(window, imageManager);
	sprite.setTexture(texture);
	sprite.setPosition(position.x + backgroundTexturePosition.x, position.y + backgroundTexturePosition.y);
	window.draw(sprite);
}