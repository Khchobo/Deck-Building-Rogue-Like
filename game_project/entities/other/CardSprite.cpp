#include "CardSprite.h"
#include <iostream>
#include "globalVariables.h"

void CardSprite::initialise(Entity deckSprite,ImageManager& imageManager)
{
	sprite.setTexture(imageManager.getImage("card2.png"));
	
	movementLocation = 2;
	inMotion = 1;
	position = deckSprite.position;
	previousPos = position;
}

void CardSprite::move(int i, WindowInfo windowInfo)
{
	
	
		if (motionPercentage == 1)
		{
			motionPercentage = 0;
			inMotion = 0;

			if (movementLocation ==2 || movementLocation ==3)
			{
				int formerPos = movementLocation;
				movementLocation = 0;
				if (i==0 && formerPos==2)
				{
					previousPos = position;
					inMotion = 1;
				}
			}
			else if (movementLocation == 4)
			{
				movementLocation = 1;
			}
			else {
				movementLocation = (movementLocation + 1) % 2;
			}

			//std::cout << position;
			return;
		}

		if (movementLocation ==2)
		{
			motionTime = 0.55;
		}
		else {
			motionTime = 0.225;
		}
		motionPercentage += frameTime / motionTime;

		if (motionPercentage > 1)
		{
			motionPercentage = 1;
		}
		//std::cout << motionPercentage << std::endl;
		switch (movementLocation) {
		case(0):
		{
			
			position.y = previousPos.y - (standaloneFunctions::easeInOut(motionPercentage) * 32);
			break;
		}
		case(1):
		{
			position.y = previousPos.y + (standaloneFunctions::easeInOut(motionPercentage) * 32);
			break;
		}
		case(2):
		//test	
			position.x = (previousPos.x* (1 - standaloneFunctions::easeInOut(motionPercentage)) + (i * 32)*( (standaloneFunctions::easeInOut(motionPercentage))));
			//std::cout << xPos<<std::endl;
			if (windowInfo.fullscreen == 0) 
			{ 
				position.y = previousPos.y * (1- standaloneFunctions::easeInOut(motionPercentage)) + ((windowInfo.activeSceneHeightTiles + 1) * 32)*(standaloneFunctions::easeInOut(motionPercentage));
			}
			else { 
				position.y = previousPos.y*(1- standaloneFunctions::easeInOut(motionPercentage)) + (sf::VideoMode::getDesktopMode().height - (windowInfo.UIHeight - 1) * 32)*(standaloneFunctions::easeInOut(motionPercentage));
			}
		case(3):
			position.x = (previousPos.x* (1 - standaloneFunctions::easeInOut(motionPercentage)) + (i * 32)*((standaloneFunctions::easeInOut(motionPercentage))));
			
			break;
		case(4):
			position.x = (previousPos.x* (1 - standaloneFunctions::easeInOut(motionPercentage)) + (i * 32)*((standaloneFunctions::easeInOut(motionPercentage))));
			position.y = previousPos.y - (standaloneFunctions::easeInOut(motionPercentage) * 32);
		default:
			break;
		}

}
