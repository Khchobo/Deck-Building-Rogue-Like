#pragma once
#include "entities\characters\BattlingCharacter.h"
#include <string>
#include "Astar.hpp"

class Enemy : public BattlingCharacter
{
public:
	Enemy(BattlingCharacterType* type, std::string identity, int xPos, int yPos, WindowInfo windowInfo);

	void action(int targetX, int targetY, WindowInfo windowInfo, std::vector<std::vector<int>> walkableTiles);
	AStar::CoordinateList currentPath;
private:
	float movementTimeout;
	int const pathUpdateTimeoutInterval = 10; //how many frames the path is updated
	int pathUpdateTimeout; // the actual coundown from pathUpdateTimeoutInterval
	AStar::CoordinateList pathfindNextSpace(int targetX, int targetY, WindowInfo windowInfo, std::vector<std::vector<int>> walkableTiles);
};

