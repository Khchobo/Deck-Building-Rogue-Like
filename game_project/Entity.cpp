#include "Entity.h"


void Entity::initialise(std::string fileName,float x, float y,bool offset)
{
	//offset is whether to position relative to the top right corner or the middle of the texture.
	
	texture.loadFromFile(fileName);
	sprite.setTexture(texture);

	if (offset==0)
	{
		xPos = x;
		yPos = y;
	}
	else
	{
		xPos = x-texture.getSize().x/2;
		yPos = y- texture.getSize().y / 2;
	}
}

void Entity::draw(sf::RenderWindow& window)
{
	sprite.setPosition(xPos, yPos);
	window.draw(sprite);
}

void Entity::animationUpdate()
	{
		//todo
	}


void Entity::animationNew(std::string name)
{
	assert(animationMap.find(name) != animationMap.end());
	currentAnimation = name;
	currentAnimationFrameNumber = 0;
};