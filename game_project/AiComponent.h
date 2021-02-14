#pragma once
#include "entities/other/Entity.h"
#include "entities\characters\BattlingCharacter.h"
#include "Astar.hpp"

const float INF = std::numeric_limits<float>::infinity();

enum class AiMoveState { chase, flee };

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

class AiComponent :
	public Entity
{
public:
	AiComponent(std::string identity, Entity* parentObject, Entity* rootObject) : Entity(identity, parentObject, rootObject) {}

	void Update() override;
	void Initialise() override;

	AStar::CoordinateList GetCurrentPath();

private:
	AStar::CoordinateList PathfindNextSpace(int targetX, int targetY, std::vector<std::vector<int>> walkableTiles);
	LocationWithDistance ClosestPlayerActionPointInRange(const CardActionMap cardActionMap);
	sf::Vector2i ChooseFleePoint(const sf::Vector2i playerTilePos, const std::vector<std::vector<int>>& collisionMap);
	void UpdatePath(std::vector<std::vector<int>> collisionMap, CardActionMap cardActionMap);

	AStar::CoordinateList m_currentPath;
	float m_movementTimeout;
	AiMoveState m_aiMoveState = AiMoveState::chase;
	int const m_pathUpdateTimeoutInterval = 30; //how many frames the path is updated
	int m_pathUpdateTimeout; // the actual coundown from pathUpdateTimeoutInterval

	sf::Vector2i m_aiTarget;

	//the time after which the ai switches back to chase mode (seconds)
	float const m_aiFleeTimeout = 0.5;
	//varaible that tracks how long left in the Ai flee state
	float m_aiFleeCountdown;
	//point the enemy flees from TODO really could do with naming something better
	LocationWithDistance m_fleePointLocation;
};

