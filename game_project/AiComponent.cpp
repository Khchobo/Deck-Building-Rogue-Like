#include "AiComponent.h"
#include "Enemy.h"

void AiComponent::Initialise()
{
	m_pathUpdateTimeout = 0;
	m_movementTimeout = dynamic_cast<BattlingCharacter*>(m_pParentObject)->m_battlingCharacterType->movementTimeoutChase;
}

void AiComponent::Update()
{
	BattlingCharacter* pBattlingCharacterParent = dynamic_cast<BattlingCharacter*>(m_pParentObject);
	Enemy* pEnemyParent = dynamic_cast<Enemy*>(m_pParentObject);
	switch (m_aiMoveState)
	{
	case AiMoveState::chase:
		//Check if any player active action points are in range
		m_aiTarget = *pEnemyParent->m_pPlayerTilePos;
		m_fleePointLocation = ClosestPlayerActionPointInRange(*pEnemyParent->m_pCardActionMap);
		if (m_fleePointLocation.distance != INF)
		{
			m_movementTimeout = 0;
			m_aiMoveState = AiMoveState::flee;
			m_aiFleeCountdown = m_aiFleeTimeout;
			//The opposite direction and equal magnitude of the vector between the current location and the action point it is fleeing from
			m_aiTarget = ChooseFleePoint(*pEnemyParent->m_pPlayerTilePos, *pEnemyParent->m_pCollisionMap);
			//update path immediately to prevent it continuing on the old path
			UpdatePath(*pEnemyParent->m_pCollisionMap, *pEnemyParent->m_pCardActionMap);
		}
		break;
	case AiMoveState::flee:
		m_aiFleeCountdown -= frameTime;
		if (m_aiFleeCountdown <= 0 && (ClosestPlayerActionPointInRange(*pEnemyParent->m_pCardActionMap).distance == INF))
		{
			m_aiMoveState = AiMoveState::chase;
		}
		break;
	}

	if (pBattlingCharacterParent->GetActionState() != actionState::death)
	{
		m_pathUpdateTimeout--;
		if (m_pathUpdateTimeout <= 0)
		{
			UpdatePath(*pEnemyParent->m_pCollisionMap,*pEnemyParent->m_pCardActionMap);
		}


		//Movement
		m_movementTimeout -= frameTime;
		if (m_movementTimeout <= 0)
		{
			pBattlingCharacterParent->m_behaviourTriggers[initiateMotion] = true;

			for (unsigned int i = 1; i < m_currentPath.size(); i++)
			{
				if (pBattlingCharacterParent->m_currentTilePos.x > m_currentPath[1].x)
				{
					if (pBattlingCharacterParent->GetDirection() != 1) pBattlingCharacterParent->m_behaviourTriggers[directionChange] = true;
					pBattlingCharacterParent->SetDirection(1);
					break;
				}
				else if (pBattlingCharacterParent->m_currentTilePos.x < m_currentPath[1].x)
				{
					if (pBattlingCharacterParent->GetDirection() != 3) pBattlingCharacterParent->m_behaviourTriggers[directionChange] = true;
					pBattlingCharacterParent->SetDirection(3);
					break;
				}
				else if (pBattlingCharacterParent->m_currentTilePos.y > m_currentPath[1].y)
				{
					if (pBattlingCharacterParent->GetDirection() != 0) pBattlingCharacterParent->m_behaviourTriggers[directionChange] = true;
					pBattlingCharacterParent->SetDirection(0);

				}
				else if (pBattlingCharacterParent->m_currentTilePos.y < m_currentPath[1].y)
				{
					if (pBattlingCharacterParent->GetDirection() != 2) pBattlingCharacterParent->m_behaviourTriggers[directionChange] = true;
					pBattlingCharacterParent->SetDirection(2);
				}
			}

			switch (m_aiMoveState)
			{
			case AiMoveState::chase:
				m_movementTimeout = pBattlingCharacterParent->m_battlingCharacterType->movementTimeoutChase + -0.3 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.3 + 0.3)));
				break;
			case AiMoveState::flee:
				m_movementTimeout = pBattlingCharacterParent->m_battlingCharacterType->movementTimeoutFlee;
			}

		}
	}
}

AStar::CoordinateList AiComponent::GetCurrentPath()
{
	return m_currentPath;
}

//TODO Much of this code is reused from the example on the git page for the pathfinder library but I seriously need
//to reduce the nesting levels for readability
//I'm pretty sure windowInfo isn't doing anything here and can be removed from arguments
AStar::CoordinateList AiComponent::PathfindNextSpace(int targetX, int targetY, std::vector<std::vector<int>> walkableTiles)
{
	BattlingCharacter* pBattlingCharacterParent = dynamic_cast<BattlingCharacter*>(m_pParentObject);

	AStar::Generator generator;
	// Set 2d map size.
	generator.setWorldSize({ static_cast<int>(walkableTiles[0].size()), static_cast<int>(walkableTiles.size()) });
	// You can use a few heuristics : manhattan, euclidean or octagonal.
	generator.setHeuristic(AStar::Heuristic::euclidean);
	generator.setDiagonalMovement(false);

	for (unsigned int i = 0; i < walkableTiles.size(); i++)
	{
		for (unsigned int j = 0; j < walkableTiles[0].size(); j++) {
			if (walkableTiles[i][j] == 0)
			{
				generator.addCollision({ static_cast<signed int>(j),static_cast<signed int>(i) });
			}
		}
	}
	AStar::CoordinateList path = generator.findPath({ targetX, targetY }, { pBattlingCharacterParent->m_currentTilePos.x, pBattlingCharacterParent->m_currentTilePos.y });
	return path;
}


LocationWithDistance AiComponent::ClosestPlayerActionPointInRange(const CardActionMap cardActionMap)
{
	BattlingCharacter* pBattlingCharacterParent = dynamic_cast<BattlingCharacter*>(m_pParentObject);

	LocationWithDistance closest = LocationWithDistance();
	for (CardAction cardAction : cardActionMap.cardActionMap)
	{
		if (cardAction.active) //TODO and player condition
		{
			LocationWithDistance candidate = LocationWithDistance(sf::Vector2i(cardAction.xPos, cardAction.yPos), pBattlingCharacterParent->m_currentTilePos);

			if ((candidate.distance <= pBattlingCharacterParent->m_battlingCharacterType->attackVisionRadius) && (candidate.distance <= closest.distance))
			{
				closest = candidate;
			}
		}
	}

	return closest;
}

//this function 'casts a ray' in the direction opposite to the vector between the player and the enemy and will return
//the furthest away walkable space with direct line of sight along this vector. this is used to choose a point to run away to
//the concept of casting a ray in this discrete space is done by stepping along a normalised version of the aforementioned vector
//and rounding the result to the nearest grid cell
//Later I should look for a better solution that this as it will lead to enemies getting stuck on corners and the like
//Perhaps once it reaches that point it can move in any direction that moves it further from the player
sf::Vector2i AiComponent::ChooseFleePoint(const sf::Vector2i playerTilePos, const std::vector<std::vector<int>>& collisionMap)
{
	BattlingCharacter* pBattlingCharacterParent = dynamic_cast<BattlingCharacter*>(m_pParentObject);

	sf::Vector2i directionVector = sf::Vector2i(pBattlingCharacterParent->m_currentTilePos.x - playerTilePos.x, pBattlingCharacterParent->m_currentTilePos.y - playerTilePos.y);
	std::cout << directionVector.x << " " << directionVector.y << "  ";
	float magnitude = sqrtf(powf(static_cast<float>(directionVector.x), 2) + powf(static_cast<float>(directionVector.y), 2));
	//multiply the normalised vector as with a magnitude of one it is too small to produce accurate results when rounded
	sf::Vector2f normalisedVector = sf::Vector2f((directionVector.x / magnitude), (directionVector.y / magnitude));
	//the line of sight algorithm checks between the enemy location and the working location. start off at the enemy location
	//and repeatedly step along the normalised vector.
	sf::Vector2i workingLocation = sf::Vector2i(pBattlingCharacterParent->m_currentTilePos.x, pBattlingCharacterParent->m_currentTilePos.y);
	bool flag = true;
	while (flag)
	{
		sf::Vector2i tempLocation = sf::Vector2i((int)(workingLocation.x + ceil(normalisedVector.x)), (int)(workingLocation.y + ceil(normalisedVector.y)));

		if (collisionMap[tempLocation.y][tempLocation.x] == 1)
		{
			break;
		}

		std::vector<sf::Vector2u> path = lineOfSight(pBattlingCharacterParent->m_currentTilePos.x, pBattlingCharacterParent->m_currentTilePos.y, (int)round(workingLocation.x), (int)round(workingLocation.y));

		for (sf::Vector2u point : path)
		{
			if (point.y<0 || point.y>collisionMap.size() || point.x<0 || point.x>collisionMap[0].size())
			{
				flag = false;
				break;
			}
			//std::cout << (collisionMap[point.y][point.x] == 1) << std::endl;
			if (collisionMap[point.y][point.x] == 1)
			{
				flag = false;
				break;
			}
		}
		workingLocation = tempLocation;
	}
	return sf::Vector2i((int)round(workingLocation.x), (int)round(workingLocation.y));
}

void AiComponent::UpdatePath(std::vector<std::vector<int>> collisionMap, CardActionMap cardActionMap)
{
	for (unsigned int i = 0; i < collisionMap.size(); i++)
	{
		for (unsigned int j = 0; j < collisionMap[0].size(); j++)
		{
			//format for the collision map in the a star algorithm has 1's and 0's inverted from the format used elsewhere
			//ie 1 indicates a walkable time, 0 a solid tile
			collisionMap[i][j] = (collisionMap[i][j] + 1) % 2;


		}
	}

	for (CardAction cardAction : cardActionMap.cardActionMap)
	{
		if (cardAction.active) //add player ID condition to this
		{
			//collisionMap[cardAction.yPos][cardAction.xPos] = 0;
		}
	}

	m_pathUpdateTimeout = m_pathUpdateTimeoutInterval + -5 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (10)));;
	m_currentPath = PathfindNextSpace(m_aiTarget.x, m_aiTarget.y, collisionMap);
}