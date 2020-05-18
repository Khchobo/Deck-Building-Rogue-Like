#include "player.h"

void Player::action(std::map<int, bool> keyboardArray, float& playerDistanceFromEdgeX, float& playerDistanceFromEdgeY,
	std::vector<std::vector<int>>& collision, WindowInfo windowInfo)
{
	bool flag = false;
	if (keyboardArray[sf::Keyboard::W])
	{
		
		direction = 0;
		flag = true;
	}
	else if (keyboardArray[sf::Keyboard::A])
	{
		direction = 1;
		flag = true;
	}
	else if (keyboardArray[sf::Keyboard::S])
	{
		direction = 2;
		flag = true;
	}
	else if (keyboardArray[sf::Keyboard::D])
	{
		direction = 3;
		flag = true;
	}
	
	if (flag && cardPoints>cardPointsStepCost && !(inMotion))
	{
		move(direction, playerDistanceFromEdgeX, playerDistanceFromEdgeY, collision, windowInfo);
	}
	//std::cout << inMotion;

	if (inMotion == 1)
	{
		//once motion is completed, end in motion state and change tile alignement 
		if (motionPercentage == 1)
		{
			inMotion = 0;
			currentXTilePos = futureXTilePos;
			currentYTilePos = futureYTilePos;
		}

		//motion percentage determined according to frame time to keep motion speed constant regardless of framerate
		motionPercentage += frameTime / motionTime;

		//cap the percentage at 1
		if (motionPercentage > 1)
		{
			motionPercentage = 1;
		}

		float newXPos;
		float newYPos;


		newXPos = (currentXTilePos + standaloneFunctions::easeInOut(motionPercentage) * (futureXTilePos - currentXTilePos))*windowInfo.tileSizeInPixels;
		newYPos = (currentYTilePos + standaloneFunctions::easeInOut(motionPercentage) * (futureYTilePos - currentYTilePos))*windowInfo.tileSizeInPixels;

		//the difference between the location on this frame and the previous frame
		float distanceMovedX = newXPos - xPos;
		float distanceMovedY = newYPos - yPos;

		//ensures the player stays bounded within the screen scroll static region
		playerDistanceFromEdgeX = min(max(static_cast<float>(80),playerDistanceFromEdgeX+distanceMovedX), static_cast<float>((windowInfo.activeSceneWidthPixels-windowInfo.tileSizeInPixels) - 80));
		playerDistanceFromEdgeY = min(max(static_cast<float>(80), playerDistanceFromEdgeY + distanceMovedY), static_cast<float>((windowInfo.activeSceneWidthPixels - windowInfo.tileSizeInPixels) - 80));

		//update the location as a linear interpolation between the old location and new, weighted by motion percentage
		xPos = newXPos;
		yPos = newYPos;

		std::cout <<"x:"<< xPos << " Y:" << yPos << std::endl;
	}
}

void Player::move(unsigned int direction, float& playerDistanceFromEdgeX,
	float& playerDistanceFromEdgeY, std::vector<std::vector<int>>& collision, WindowInfo windowInfo)
{

	switch (direction) {
		//up
	case(0):
		futureXTilePos = currentXTilePos;
		futureYTilePos = currentYTilePos - 1;
		break;
		//left
	case(1):
		futureXTilePos = currentXTilePos - 1;
		futureYTilePos = currentYTilePos;
		break;
		//down
	case(2):
		futureXTilePos = currentXTilePos;
		futureYTilePos = currentYTilePos + 1;
		break;
		//right
	case(3):
		futureXTilePos = currentXTilePos + 1;
		futureYTilePos = currentYTilePos;
		break;
	}
	if (collision[futureYTilePos][futureXTilePos] == 0)
	{
		cardPoints -= cardPointsStepCost;
		inMotion = true;
		motionPercentage = 0.0;
	}
}

void Player::draw(sf::RenderWindow& window, float backgroundXPos, float backgroundYPos)
{
	sprite.setTexture(texture);
	sprite.setPosition(xPos + backgroundXPos, yPos + backgroundYPos);
	window.draw(sprite);
}