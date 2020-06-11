#include "Enemy.h"



Enemy::Enemy(BattlingCharacterType* type, std::string identity, sf::Vector2i tilePosition,WindowInfo windowInfo,ImageManager& imageManager)
	: BattlingCharacter(type, identity, imageManager)
{
	texture.loadFromFile("assets/slime.png");
	currentTilePos = tilePosition;

	position = sf::Vector2f(currentTilePos.x * windowInfo.tileSizeInPixels,currentTilePos.y * windowInfo.tileSizeInPixels);
	pathUpdateTimeout = 0;
	movementTimeout = type->movementTimeoutChase;
	directionalArrow.initialise("directionalArrow.png", position, 0,imageManager);
}

void Enemy::action(sf::Vector2i playerTilePos, WindowInfo windowInfo, CardActionMap cardActionMap, std::vector<std::vector<int>> collisionMap)
{
	resetBehaviourTriggers();


	
	switch (aiMoveState)
	{
	case aiMoveState::chase:
		//Check if any player active action points are in range
		AiTarget = playerTilePos;
		closest = closestPlayerActionPointInRange(cardActionMap);
		if (closest.distance != INF)
		{
			movementTimeout=0;
			aiMoveState = aiMoveState::flee;
			AiFleeCountdown = AiFleeTimeout;
			//The opposite direction and equal magnitude of the vector between the current location and the action point it is fleeing from
			AiTarget = chooseFleePoint(playerTilePos, collisionMap);
			//update path immediately to prevent it continuing on the old path
			updatePath(collisionMap, cardActionMap, windowInfo);
		}
		break;	
	case aiMoveState::flee:
		AiFleeCountdown -= frameTime;
		if( AiFleeCountdown <= 0 && (closestPlayerActionPointInRange(cardActionMap).distance==INF))
		{
			aiMoveState = aiMoveState::chase;
		}
		break;
	}
	
	if (actionstate != actionState::death)
	{
		pathUpdateTimeout--;
		if (pathUpdateTimeout <= 0)
		{
			updatePath(collisionMap, cardActionMap, windowInfo);
		}


		//Movement
		movementTimeout -= frameTime;
		if (movementTimeout <= 0)
		{
			behaviourTriggers[initiateMotion] = true;

			for (int i = 1; i < currentPath.size(); i++)
			{
				if (currentTilePos.x > currentPath[1].x)
				{
					if (direction != 1) behaviourTriggers[directionChange] = true;
					direction = 1;
					break;
				}
				else if (currentTilePos.x < currentPath[1].x)
				{
					if (direction != 3) behaviourTriggers[directionChange] = true;
					direction = 3;
					break;
				}
				else if (currentTilePos.y > currentPath[1].y)
				{
					if (direction != 0) behaviourTriggers[directionChange] = true;
					direction = 0;

				}
				else if (currentTilePos.y < currentPath[1].y)
				{
					if (direction != 2) behaviourTriggers[directionChange] = true;
					direction = 2;
				}
			}

			switch (aiMoveState)
			{
			case aiMoveState::chase:
				movementTimeout = type->movementTimeoutChase;
				break;
			case aiMoveState::flee:
				movementTimeout = type->movementTimeoutFlee;
			}

		}
	}
	BattlingCharacter::action(collisionMap,windowInfo, 1, direction, cardActionMap);
}


//TODO Much of this code is reused from the example on the git page for the pathfinder library but I seriously need
//to reduce the nesting levels for readability
//I'm pretty sure windowInfo isn't doing anything here and can be removed from arguments
AStar::CoordinateList Enemy::pathfindNextSpace(int targetX, int targetY, WindowInfo windowInfo, std::vector<std::vector<int>> walkableTiles)
{

	AStar::Generator generator;
	// Set 2d map size.
	generator.setWorldSize({ static_cast<int>(walkableTiles[0].size()), static_cast<int>(walkableTiles.size()) });
	// You can use a few heuristics : manhattan, euclidean or octagonal.
	generator.setHeuristic(AStar::Heuristic::euclidean);
	generator.setDiagonalMovement(false);

	for (int i = 0; i < walkableTiles.size(); i++)
	{
		for (int j = 0; j < walkableTiles[0].size(); j++) {
			if (walkableTiles[i][j] == 0)
			{
				generator.addCollision({ j,i });
			}
		}
	}
	AStar::CoordinateList path = generator.findPath({ targetX, targetY }, { currentTilePos.x, currentTilePos.y });
	return path;
}


LocationWithDistance Enemy::closestPlayerActionPointInRange(CardActionMap cardActionMap)
{
	LocationWithDistance closest = LocationWithDistance();
	for (CardAction cardAction: cardActionMap.cardActionMap)
	{
			if (cardAction.active) //TODO and player condition
			{
				LocationWithDistance candidate = LocationWithDistance(sf::Vector2i(cardAction.xPos, cardAction.yPos), currentTilePos);

				if ((candidate.distance <= type->attackVisionRadius) && (candidate.distance <= closest.distance))
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
sf::Vector2i Enemy::chooseFleePoint(sf::Vector2i playerTilePos, std::vector<std::vector<int>>& collisionMap)
{
	sf::Vector2i directionVector = sf::Vector2i(currentTilePos.x - playerTilePos.x, currentTilePos.y - playerTilePos.y);
	std::cout << directionVector.x << " " << directionVector.y<<"  ";
	float magnitude = sqrt(pow(directionVector.x, 2) + pow(directionVector.y, 2));
	//multiply the normalised vector as with a magnitude of one it is too small to produce accurate results when rounded
	sf::Vector2f normalisedVector = sf::Vector2f((directionVector.x / magnitude), (directionVector.y / magnitude));
	//the line of sight algorithm checks between the enemy location and the working location. start off at the enemy location
	//and repeatedly step along the normalised vector.
	sf::Vector2f workingLocation = sf::Vector2f(float(currentTilePos.x), float(currentTilePos.y));
	bool flag = true;
	while (flag)
	{
		sf::Vector2f tempLocation = sf::Vector2f(workingLocation.x + normalisedVector.x, workingLocation.y + normalisedVector.y);

		if (collisionMap[tempLocation.y][tempLocation.x] == 1)
		{
			break;
		}

		std::vector<sf::Vector2i> path = lineOfSight(currentTilePos.x, currentTilePos.y, round(workingLocation.x), round(workingLocation.y));

		for (sf::Vector2i point : path)
		{
			if (point.y<0 || point.y>collisionMap.size() || point.x<0 || point.x>collisionMap[0].size())
			{
				flag = false;
				break;
			}
			std::cout << (collisionMap[point.y][point.x] == 1) << std::endl;
			if (collisionMap[point.y][point.x] == 1)
			{
				flag = false;
				break;
			}
		}
		workingLocation = tempLocation;
	}
	return sf::Vector2i(round(workingLocation.x),round(workingLocation.y));
}

void Enemy::updatePath(std::vector<std::vector<int>> collisionMap, CardActionMap cardActionMap, WindowInfo windowInfo)
{
	for (int i = 0; i < collisionMap.size(); i++)
	{
		for (int j = 0; j < collisionMap[0].size(); j++)
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

	pathUpdateTimeout = pathUpdateTimeoutInterval;
	currentPath = pathfindNextSpace(AiTarget.x, AiTarget.y, windowInfo, collisionMap);
}