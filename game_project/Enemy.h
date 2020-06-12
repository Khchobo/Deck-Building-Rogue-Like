#pragma once
#include "entities\characters\BattlingCharacter.h"
#include <string>
#include "Astar.hpp"

const float INF = std::numeric_limits<float>::infinity();

enum class aiMoveState{chase,flee};

struct LocationWithDistance
{
	LocationWithDistance() {
		distance = INF;
	}
	LocationWithDistance(sf::Vector2i selfLocation, sf::Vector2i parentLocation) : location(selfLocation)
	{
		//euclidean distance
		distance = sqrtf(powf(static_cast<float>(selfLocation.x - parentLocation.x), 2.0f) + powf(static_cast<float>(selfLocation.y - parentLocation.y), 2.0f));
	}

	sf::Vector2i location;
	float distance;
};

class Enemy : public BattlingCharacter
{
public:

	Enemy(BattlingCharacterType* type, std::string identity, sf::Vector2i tilePosition, WindowInfo windowInfo, ImageManager& imageManager);

	void action(sf::Vector2i playerTilePos, WindowInfo windowInfo, CardActionMap cardActionMap, std::vector<std::vector<int>> collision);
	AStar::CoordinateList currentPath;
private:
	float movementTimeout;
	aiMoveState aiMoveState= aiMoveState::chase;
	int const pathUpdateTimeoutInterval = 10; //how many frames the path is updated
	int pathUpdateTimeout; // the actual coundown from pathUpdateTimeoutInterval
	AStar::CoordinateList pathfindNextSpace(int targetX, int targetY, WindowInfo windowInfo, std::vector<std::vector<int>> walkableTiles);
	LocationWithDistance closestPlayerActionPointInRange(CardActionMap cardActionMap);
	sf::Vector2i AiTarget;
	void updatePath(std::vector<std::vector<int>> collisionMap, CardActionMap cardActionMap, WindowInfo windowInfo);
	//the time after which the ai switches back to chase mode (seconds)
	float const AiFleeTimeout=0.5;
	//varaible that tracks how long left in the Ai flee state
	float AiFleeCountdown;
	//point the enemy flees from TODO really could do with naming something better
	LocationWithDistance closest;
	sf::Vector2i chooseFleePoint(sf::Vector2i playerTilePos, std::vector<std::vector<int>>& collisionMap);
};

