#pragma once
#include "entities\characters\BattlingCharacter.h"
#include <string>
#include "Astar.hpp"

class Enemy : public BattlingCharacter
{
public:
	Enemy(BattlingCharacterType* type, std::string identity, sf::Vector2i tilePosition, ImageManager* imageManager);

	virtual void Initialise() override { return; }

	virtual void Update() override { return; }

	void Update(sf::Vector2i& playerTilePos, CardActionMap& cardActionMap, std::vector<std::vector<int>>& collisionMap);

	sf::Vector2i* m_pPlayerTilePos;
	CardActionMap* m_pCardActionMap;
	std::vector<std::vector<int>>* m_pCollisionMap;

};

