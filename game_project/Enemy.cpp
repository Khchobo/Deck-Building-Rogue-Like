#include "Enemy.h"


Enemy::Enemy(BattlingCharacterType* type, std::string identity, int xPos, int yPos,WindowInfo windowInfo) : BattlingCharacter(type, identity)
{
	currentXTilePos = xPos;
	currentYTilePos = yPos;

	xPos = currentXTilePos * windowInfo.tileSizeInPixels;
	yPos = currentYTilePos * windowInfo.tileSizeInPixels;

}

AStar::CoordinateList Enemy::action(int targetX, int targetY, WindowInfo windowInfo, std::vector<std::vector<int>> walkableTiles)
{
	return pathfindNextSpace(targetX, targetY, windowInfo, walkableTiles);
}


//TODO Much of this code is reused from the example on the git page for the pathfinder library but I seriously need
//to reduce the nesting levels for readability
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
	AStar::CoordinateList path = generator.findPath({ targetX, targetY }, { currentXTilePos, currentYTilePos });
	return path;
}