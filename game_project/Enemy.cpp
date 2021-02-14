#include "Enemy.h"
#include "AiComponent.h"


Enemy::Enemy(BattlingCharacterType* type, std::string identity, sf::Vector2i tilePosition, ImageManager* imageManager)
	: BattlingCharacter(type, identity, imageManager, sf::Vector2f(10*windowInfo.tileSizeInPixels, 10 * windowInfo.tileSizeInPixels)) //TODO temporary until we define the enemy position externally
{
	m_currentTilePos = tilePosition;
	position = sf::Vector2f(static_cast<float>(m_currentTilePos.x * windowInfo.tileSizeInPixels),static_cast<float>(m_currentTilePos.y * windowInfo.tileSizeInPixels));
	m_components.emplace_back(std::make_shared<AiComponent>("AiComponent", this, this));
}

void Enemy::Update(sf::Vector2i& playerTilePos, CardActionMap& cardActionMap, std::vector<std::vector<int>>& collisionMap)
{
	ResetBehaviourTriggers();

	m_pPlayerTilePos = &playerTilePos;
	m_pCardActionMap = &cardActionMap;
	m_pCollisionMap = &collisionMap;

	GET_COMPONENT(AiComponent, "AiComponent")->Update();

	BattlingCharacter::Update(collisionMap, 1, m_direction, cardActionMap);
}

