#include "player.h"
#include "easeInOut.h"

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


		newXPos = (currentXTilePos + easeInOut(motionPercentage) * (futureXTilePos - currentXTilePos))*tileSize*pixelSize;
		newYPos = (currentYTilePos + easeInOut(motionPercentage) * (futureYTilePos - currentYTilePos))*tileSize*pixelSize;

		//the difference between the location on this frame and the previous frame
		float distanceMovedX = newXPos - xPos;
		float distanceMovedY = newYPos - yPos;

		//ensures the player stays bounded within the screen scroll static region
		playerDistanceFromEdgeX = min(max(static_cast<float>(80),playerDistanceFromEdgeX+distanceMovedX), static_cast<float>((windowInfo.windowWidth - 1) * tileSize*pixelSize - 80));
		playerDistanceFromEdgeY = min(max(static_cast<float>(80), playerDistanceFromEdgeY + distanceMovedY), static_cast<float>((windowInfo.windowHeight - 1) * tileSize*pixelSize - 80));

		//update the location as a linear interpolation between the old location and new, weighted by motion percentage
		xPos = newXPos;
		yPos = newYPos;

	}
}

void Player::move(unsigned int direction, float& playerDistanceFromEdgeX,
	float& playerDistanceFromEdgeY, std::vector<std::vector<int>>& collision, WindowInfo windowInfo)
{
	switch(movementMode)
	{ 
		{
	case(0):

		//The X and Y of the potential character location after moving (in grid references rather than absolute location)
		int futureLocX;
		int futureLocY;


		//TODO change 32 to pixelsize*tilesize
		switch (direction)
		{
			//up
		case (0):

			futureLocX = floor((xPos) / 32);
			futureLocY = floor((yPos - (speed *frameTime)) / 32);

			if (collision[futureLocY][futureLocX] == 0
				&& collision[futureLocY + 1][futureLocX] == 0
				&& collision[futureLocY][futureLocX + 1] == 0
				&& collision[futureLocY + 1][futureLocX + 1] == 0) {
				yPos -= (speed *frameTime);
				if (!(playerDistanceFromEdgeY < 80))
				{
					playerDistanceFromEdgeY -= (speed *frameTime);
				}
			}

			break;
			//left

		case (1):
			futureLocX = floor((xPos - (speed *frameTime)) / 32);
			futureLocY = floor(yPos / 32);

			//Need to check each of the four courners of our character
			if (collision[futureLocY][futureLocX] == 0
				&& collision[futureLocY + 1][futureLocX] == 0
				&& collision[futureLocY][futureLocX + 1] == 0
				&& collision[futureLocY + 1][futureLocX + 1] == 0)
			{
				xPos -= (speed *frameTime);

				if (!(playerDistanceFromEdgeX < (80)))
				{
					playerDistanceFromEdgeX -= (speed *frameTime);
				}
			}
			break;

			//down
		case (2):
			futureLocX = floor((xPos) / 32);
			futureLocY = floor((yPos + (speed *frameTime)) / 32);

			if (collision[futureLocY][futureLocX] == 0
				&& collision[futureLocY + 1][futureLocX] == 0
				&& collision[futureLocY][futureLocX + 1] == 0
				&& collision[futureLocY + 1][futureLocX + 1] == 0) {
				yPos += (speed *frameTime);

				if (!(playerDistanceFromEdgeY > ((windowInfo.windowHeight - 1) * 16 * 2 - 80)))
				{
					playerDistanceFromEdgeY += (speed *frameTime);
				}

			}
			break;

			//right
		case (3):
			futureLocX = floor((xPos + (speed *frameTime)) / 32);
			futureLocY = floor(yPos / 32);

			if (collision[futureLocY][futureLocX] == 0
				&& collision[futureLocY + 1][futureLocX] == 0
				&& collision[futureLocY][futureLocX + 1] == 0
				&& collision[futureLocY + 1][futureLocX + 1] == 0) {
				xPos += (speed *frameTime);
				if (!(playerDistanceFromEdgeX > ((windowInfo.windowWidth - 1) * 16 * 2 - 80)))
				{
					playerDistanceFromEdgeX += (speed *frameTime);
				}
			}
			break;
		default:
			break;
		}
		break;
		}
	case(1):
		
			switch (direction){
			//up
			case(0):
				futureXTilePos=currentXTilePos;
				futureYTilePos=currentYTilePos-1;
				break;
			//left
			case(1):
				futureXTilePos = currentXTilePos-1;
				futureYTilePos = currentYTilePos;
				break;
			//down
			case(2):
				futureXTilePos = currentXTilePos;
				futureYTilePos = currentYTilePos+1;
				break;
			//right
			case(3):
				futureXTilePos = currentXTilePos+1;
				futureYTilePos = currentYTilePos;
				break;
			}
			if(collision[futureYTilePos][futureXTilePos]==0)
			{
				cardPoints -= cardPointsStepCost;
				inMotion = true;
				motionPercentage = 0.0;
			}
			break;
	default:
		break;
	}
}

void Player::draw(sf::RenderWindow& window, float backgroundXPos, float backgroundYPos)
{
	sprite.setTexture(texture);
	sprite.setPosition(xPos + backgroundXPos, yPos + backgroundYPos);
	window.draw(sprite);
}