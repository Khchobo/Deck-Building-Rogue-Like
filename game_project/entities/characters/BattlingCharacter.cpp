#include "BattlingCharacter.h"
#include "AnimationManager.h"

BattlingCharacter::BattlingCharacter(BattlingCharacterType* type, std::string identity, ImageManager* imageManager, sf::Vector2f pos) : 
	PositionalEntity(identity, pos, imageManager, identity,	this, this), //todo replace with filename
m_cardsInHand(1, imageManager, this), m_cardsInDeck(type), m_battlingCharacterType(type), m_directionalArrow("directionalArrow", imageManager, "directionalArrow", (Entity*)this, (Entity*)this)
{
	m_currentTilePos = sf::Vector2i(pos.x/windowInfo.tileSizeInPixels, pos.y/ windowInfo.tileSizeInPixels);
	//type->identifier = identity;
	m_cardPoints = type->cardPointsMax;
	m_cardPointsStepCost = 5;
	m_health = type->maxHealth;
	m_direction = 0;

	ArrowDirectionUpdate();

	std::shared_ptr<AnimationManager> animationManager = std::make_shared<AnimationManager>();
	animationManager->initalise(type);
	m_components.emplace_back(std::move(animationManager));
};

void BattlingCharacter::UpdateMotion()
{
	//once motion is completed, end in motion state and change tile alignement 
	if (m_motionPercentage == 1)
	{
		m_behaviourTriggers[endMotion] = true;
		m_actionState = actionState::idle;
		m_currentTilePos = m_futureTilePos;
	}

	//motion percentage determined according to frame time to keep motion speed constant regardless of framerate
	m_motionPercentage += frameTime / m_battlingCharacterType->motionTime;

	//cap the percentage at 1
	if (m_motionPercentage > 1)
	{
		m_motionPercentage = 1;
	}

	float newXPos;
	float newYPos;


	newXPos = (m_currentTilePos.x + standaloneFunctions::easeInOut(m_motionPercentage) * (m_futureTilePos.x - m_currentTilePos.x))*windowInfo.tileSizeInPixels;
	newYPos = (m_currentTilePos.y + standaloneFunctions::easeInOut(m_motionPercentage) * (m_futureTilePos.y - m_currentTilePos.y))*windowInfo.tileSizeInPixels;

	m_verticalHopOffset = quadraticHop(50, m_motionPercentage);
	
	//the difference between the location on this frame and the previous frame
	m_distanceMovedX = newXPos - position.x;
	m_distanceMovedY = newYPos - m_yPosNoOffset;

	//update the location as a linear interpolation between the old location and new, weighted by motion percentage
	position.x = newXPos;
	m_yPosNoOffset = newYPos;
	position.y = newYPos-m_verticalHopOffset;
}

void BattlingCharacter::InitialiseBattleMode()
{
}

void BattlingCharacter::Update(std::vector<std::vector<int>>& collision, int renderMode, int direction, CardActionMap cardActionMap)
{


	switch (m_actionState)
	{
	case actionState::idle:
		if (m_behaviourTriggers[initiateMotion] && m_cardPoints > m_cardPointsStepCost && !(m_bInMotion))
		{
			InitiateNewMotion(direction, collision);
		}
		break;
	case actionState::move:
		UpdateMotion();
		
		break;
	default:
		break;
	}

	if (m_actionState != actionState::death)
	{

		UpdateDamageAndHealth(cardActionMap);

		if (m_behaviourTriggers[directionChange])
		{
			ArrowDirectionUpdate();
		}
		m_cardPoints = min(static_cast<float>(m_battlingCharacterType->cardPointsMax), m_cardPoints + m_battlingCharacterType->cardPointRecoveryRate*frameTime);
	}

	GET_COMPONENT(AnimationManager,"AnimationManager")->updateAnimations(m_behaviourTriggers, m_battlingCharacterType, GET_COMPONENT(Sprite,"Sprite"));
}

void BattlingCharacter::UpdateDamageAndHealth(CardActionMap cardActionMap)
{
	if (m_iFrameState == iFrameState::vunerable)
	{
		for (CardAction cardAction : cardActionMap.cardActionMap)
		{
			if (cardAction.active && sf::Vector2i(cardAction.xPos, cardAction.yPos) == m_currentTilePos && cardAction.characterType!=m_battlingCharacterType->characterType)
			{
				m_health -= cardAction.attackDamage;
				m_behaviourTriggers[takeDamage] = true;
				m_iFrameState = iFrameState::invincible;
			}
		}
	}
	if (m_health <= 0)
	{
		m_behaviourTriggers[triggerDeath] = true;
		m_actionState = actionState::death;
	}
}

void BattlingCharacter::ArrowDirectionUpdate()
{
	float directionalArrowRotation;
	switch (m_direction)
	{
	case(0):
		m_directionalArrow.position = sf::Vector2f(0, -24);
		directionalArrowRotation = 0;
		break;
	case(1):
		m_directionalArrow.position = sf::Vector2f(-24, 0);
		directionalArrowRotation = 270;
		break;
	case(2):
		m_directionalArrow.position = sf::Vector2f(0, 24);
		directionalArrowRotation = 180;
		break;
	case(3):
		m_directionalArrow.position = sf::Vector2f(24, 0);
		directionalArrowRotation = 90;
		break;
	default:
		throw std::invalid_argument("Direction cannot take value" + std::to_string(m_direction));
	}
	GET_OBJECT_COMPONENT(Sprite, "Sprite", m_directionalArrow)->m_sprite.setRotation(directionalArrowRotation);
}

void BattlingCharacter::ResetBehaviourTriggers()
{
	std::map<BehaviourTrigger, bool>::iterator it;
	for (it = m_behaviourTriggers.begin(); it != m_behaviourTriggers.end(); it++)
	{
		m_behaviourTriggers[it->first] = false;
	}
}

void BattlingCharacter::InitiateNewMotion(unsigned int direction, std::vector<std::vector<int>>& collision)
{
	switch (direction) {
		//up
	case(0):
		m_futureTilePos = sf::Vector2i(m_currentTilePos.x, m_currentTilePos.y-1);
		break;
		//left
	case(1):
		m_futureTilePos = sf::Vector2i(m_currentTilePos.x-1, m_currentTilePos.y);
		break;
		//down
	case(2):
		m_futureTilePos = sf::Vector2i(m_currentTilePos.x, m_currentTilePos.y +1);
		break;
		//right
	case(3):
		m_futureTilePos = sf::Vector2i(m_currentTilePos.x+1, m_currentTilePos.y);
		break;
	}
	if (collision[m_futureTilePos.y][m_futureTilePos.x] == 0)
	{
		m_cardPoints -= m_cardPointsStepCost;
		m_actionState = actionState::move;
		m_motionPercentage = 0.0;
	}
}

void BattlingCharacter::DrawToScreen(sf::RenderWindow& window)
{
	//directionalArrow.position.x += windowInfo.backgroundTexturePosition.x;
	//directionalArrow.position.y += windowInfo.backgroundTexturePosition.y;
	GET_OBJECT_COMPONENT(Sprite, "Sprite", m_directionalArrow)->DrawToScreen(window, Sprite::localSpace);
	GET_COMPONENT(Sprite,"Sprite")->DrawToScreen(window, Sprite::CoordSpace::localSpace);
}