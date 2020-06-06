#pragma once
#include "entities\characters\BattlingCharacter.h"
#include <string>
#include "Astar.hpp"

class Enemy : public BattlingCharacter
{
public:
	Enemy(BattlingCharacterType* type, std::string identity, int xPos, int yPos, WindowInfo windowInfo);

	AStar::CoordinateList action(int targetX, int targetY, WindowInfo windowInfo, std::vector<std::vector<int>> walkableTiles);

private:
	float movementTimeout;
	AStar::CoordinateList pathfindNextSpace(int targetX, int targetY, WindowInfo windowInfo, std::vector<std::vector<int>> walkableTiles);
};

