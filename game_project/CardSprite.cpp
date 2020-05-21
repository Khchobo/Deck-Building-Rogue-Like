#include "CardSprite.h"
#include <iostream>
#include "globalVariables.h"


void CardSprite::initialise(Entity deckSprite)
{
	sprite.setTexture(imageManager.getImage("card2.png"));
	
	position = 2;
	inMotion = 1;
	xPos = deckSprite.xPos-32;
	yPos = deckSprite.yPos-48;
	previousXPos = xPos;
	previousYPos = yPos;
}

void CardSprite::draw(sf::RenderWindow& window)
{
	sprite.setPosition(xPos, yPos);
	window.draw(sprite);
}

void CardSprite::move(int i, WindowInfo windowInfo)
{
	
	
		if (motionPercentage == 1)
		{
			motionPercentage = 0;
			inMotion = 0;

			if (position==2 || position==3)
			{
				int formerPos = position;
				position = 0;
				if (i==0 && formerPos==2)
				{
					previousXPos = xPos;
					previousYPos = yPos;
					inMotion = 1;
				}
			}
			else if (position == 4)
			{
				position = 1;
			}
			else {
				position = (position + 1) % 2;
			}

			//std::cout << position;
			return;
		}

		if (position==2)
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
		switch (position) {
		case(0):
		{
			

			yPos = previousYPos - (standaloneFunctions::easeInOut(motionPercentage) * 32);
			break;
		}
		case(1):
		{
			yPos = previousYPos + (standaloneFunctions::easeInOut(motionPercentage) * 32);
			break;
		}
		case(2):
		//test	
			xPos = (previousXPos* (1 - standaloneFunctions::easeInOut(motionPercentage)) + (i * 32)*( (standaloneFunctions::easeInOut(motionPercentage))));
			//std::cout << xPos<<std::endl;
			if (windowInfo.fullscreen == 0) 
			{ 
				yPos = previousYPos* (1- standaloneFunctions::easeInOut(motionPercentage)) + ((windowInfo.activeSceneHeightTiles + 1) * 32)*(standaloneFunctions::easeInOut(motionPercentage));
			}
			else { 
				yPos = previousYPos* (1- standaloneFunctions::easeInOut(motionPercentage)) + (sf::VideoMode::getDesktopMode().height - (windowInfo.UIHeight - 1) * 32)*(standaloneFunctions::easeInOut(motionPercentage));
			}
		case(3):
			xPos = (previousXPos* (1 - standaloneFunctions::easeInOut(motionPercentage)) + (i * 32)*((standaloneFunctions::easeInOut(motionPercentage))));
			
			break;
		case(4):
			xPos = (previousXPos* (1 - standaloneFunctions::easeInOut(motionPercentage)) + (i * 32)*((standaloneFunctions::easeInOut(motionPercentage))));
			yPos = previousYPos - (standaloneFunctions::easeInOut(motionPercentage) * 32);
		default:
			break;
		}

}
