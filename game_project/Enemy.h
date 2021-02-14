#pragma once
#include "entities\characters\BattlingCharacter.h"
#include <string>
#include "Astar.hpp"

const float INF = std::numeric_limits<float>::infinity();

enum class AiMoveState{chase,flee};

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
	Enemy(BattlingCharacterType* type, std::string identity, sf::Vector2i tilePosition, ImageManager* imageManager);

	void Update(sf::Vector2i playerTilePos, CardActionMap cardActionMap, std::vector<std::vector<int>> collision);

	AStar::CoordinateList m_currentPath;

private:
	AStar::CoordinateList PathfindNextSpace(int targetX, int targetY, std::vector<std::vector<int>> walkableTiles);
	LocationWithDistance ClosestPlayerActionPointInRange(CardActionMap cardActionMap);
	sf::Vector2i ChooseFleePoint(sf::Vector2i playerTilePos, std::vector<std::vector<int>>& collisionMap);
	void UpdatePath(std::vector<std::vector<int>> collisionMap, CardActionMap cardActionMap);

	float m_movementTimeout;
	AiMoveState m_aiMoveState= AiMoveState::chase;
	int const m_pathUpdateTimeoutInterval = 30; //how many frames the path is updated
	int m_pathUpdateTimeout; // the actual coundown from pathUpdateTimeoutInterval

	sf::Vector2i m_aiTarget;

	//the time after which the ai switches back to chase mode (seconds)
	float const m_aiFleeTimeout=0.5;
	//varaible that tracks how long left in the Ai flee state
	float m_aiFleeCountdown;
	//point the enemy flees from TODO really could do with naming something better
	LocationWithDistance m_fleePointLocation;

};

