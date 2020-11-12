#include "BattlingCharacter.h"
#include "AnimationManager.h"

BattlingCharacter::BattlingCharacter(BattlingCharacterType* type, std::string identity, ImageManager& imageManager)  : PositionalEntity(type, identity, imageManager),
cardsInHand(1), cardsInDeck(type), type(type)
{
	//type->identifier = identity;
	cardPoints = type->cardPointsMax;
	cardPointsStepCost = 5;
	health = type->maxHealth;

	//HOTFIX
	PositionalEntity* temp=new PositionalEntity();
	temp->identity = "directionalArrow";
	temp->imageManager = &imageManager;
	directionalArrow.initialise(temp);
	delete temp;
	arrowDirectionUpdate();

	AnimationManager* animationManager = new AnimationManager();
	animationManager->initalise(type);
	components.emplace_back(std::move(animationManager));
};

void BattlingCharacter::checkForMotion() {}

void BattlingCharacter::updateMotion(WindowInfo windowInfo)
{
	//once motion is completed, end in motion state and change tile alignement 
	if (motionPercentage == 1)
	{
		behaviourTriggers[endMotion] = true;
		actionstate = actionState::idle;
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

void BattlingCharacter::action(std::vector<std::vector<int>>& collision, WindowInfo windowInfo, int renderMode, int direction, CardActionMap cardActionMap)
{


	switch (actionstate)
	{
	case actionState::idle:
		if (behaviourTriggers[initiateMotion] && cardPoints > cardPointsStepCost && !(inMotion))
		{
			initiateNewMotion(direction, collision);
		}
		break;
	case actionState::move:
		updateMotion(windowInfo);
		
		break;
	default:
		break;
	}

	if (actionstate != actionState::death)
	{

		updateDamageAndHealth(cardActionMap);

		if (behaviourTriggers[directionChange])
		{
			arrowDirectionUpdate();
		}
		cardPoints = min(static_cast<float>(type->cardPointsMax), cardPoints + type->cardPointRecoveryRate*frameTime);
	}

	GET_COMPONENT(AnimationManager,"AnimationManager")->updateAnimations(behaviourTriggers, type, GET_COMPONENT(Sprite,"Sprite"));
}

void BattlingCharacter::updateDamageAndHealth(CardActionMap cardActionMap)
{
	if (iFrameState == iFrameState::vunerable)
	{
		for (CardAction cardAction : cardActionMap.cardActionMap)
		{
			if (cardAction.active && sf::Vector2i(cardAction.xPos, cardAction.yPos) == currentTilePos && cardAction.characterType!=type->characterType)
			{
				health -= cardAction.attackDamage;
				behaviourTriggers[takeDamage] = true;
				iFrameState = iFrameState::invincible;
			}
		}
	}
	if (health <= 0)
	{
		behaviourTriggers[triggerDeath] = true;
		actionstate = actionState::death;
	}
}

void BattlingCharacter::arrowDirectionUpdate()
{
	float directionalArrowRotation;
	switch (direction)
	{
	case(0):
		directionalArrow.position = sf::Vector2f(0, -24);
		directionalArrowRotation = 0;
		break;
	case(1):
		directionalArrow.position = sf::Vector2f(-24, 0);
		directionalArrowRotation = 270;
		break;
	case(2):
		directionalArrow.position = sf::Vector2f(0, 24);
		directionalArrowRotation = 180;
		break;
	case(3):
		directionalArrow.position = sf::Vector2f(24, 0);
		directionalArrowRotation = 90;
		break;
	default:
		throw std::invalid_argument("Direction cannot take value" + std::to_string(direction));
	}
	directionalArrow.sprite.setRotation(directionalArrowRotation);
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
		actionstate = actionState::move;
		motionPercentage = 0.0;
	}
}

void BattlingCharacter::draw(sf::RenderWindow& window, const WindowInfo& windowInfo)
{
	directionalArrow.position.x += windowInfo.backgroundTexturePosition.x;
	directionalArrow.position.y += windowInfo.backgroundTexturePosition.y;
	directionalArrow.draw(window,windowInfo);
	GET_COMPONENT(Sprite,"Sprite")->draw(window, windowInfo);
}