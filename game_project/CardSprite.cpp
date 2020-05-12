#include "CardSprite.h"
#include <iostream>
#include "easeInOut.h"



void CardSprite::initialise(Entity deckSprite)
{
	texture.loadFromFile("card2.png");
	sprite.setTexture(texture);
	
	position = 2;
	inMotion = 1;
	xPos = deckSprite.xPos;
	yPos = deckSprite.yPos;
	previousXPos = xPos;
	previousYPos = yPos;
}

void CardSprite::draw(sf::RenderWindow& window)
{
	sprite.setPosition(xPos, yPos);
	window.draw(sprite);
}

void CardSprite::move(float frameTime, int i, WindowInfo windowInfo)
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
			

			yPos = previousYPos - (easeInOut(motionPercentage) * 32);
			break;
		}
		case(1):
		{
			yPos = previousYPos + (easeInOut(motionPercentage) * 32);
			break;
		}
		case(2):
			
			xPos = (previousXPos* (1 - easeInOut(motionPercentage)) + (i * 32)*( (easeInOut(motionPercentage))));
			//std::cout << xPos<<std::endl;
			if (windowInfo.fullscreen == 0) 
			{ 
				yPos = previousYPos* (1-easeInOut(motionPercentage)) + ((windowInfo.windowHeight + 1) * 32)*(easeInOut(motionPercentage));
			}
			else { 
				yPos = previousYPos* (1-easeInOut(motionPercentage)) + (sf::VideoMode::getDesktopMode().height - (windowInfo.tileReductionY - 1) * 32)*(easeInOut(motionPercentage));
			}
		case(3):
			xPos = (previousXPos* (1 - easeInOut(motionPercentage)) + (i * 32)*((easeInOut(motionPercentage))));
			
			break;
		case(4):
			xPos = (previousXPos* (1 - easeInOut(motionPercentage)) + (i * 32)*((easeInOut(motionPercentage))));
			yPos = previousYPos - (easeInOut(motionPercentage) * 32);
		default:
			break;
		}

}
