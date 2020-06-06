#include "Entity.h"

//alignmentMode is whether to position relative to the top right corner or the middle of the texture.
void Entity::initialise(std::string fileName,float x, float y,bool alignmentMode,ImageManager& imageManager)
{
	
	alignment = alignmentMode;

	sprite.setTexture(imageManager.getImage(fileName)); 
	std::cout << fileName<<std::endl<<std::endl;
	textureName = fileName;
	xPos = x;
	yPos = y;
	
}

void Entity::draw(sf::RenderWindow& window,ImageManager& imageManager)
{
	switch (alignment)
	{
	case(0):
		sprite.setPosition(xPos, yPos);
		break;
	case(1):
		sprite.setPosition(xPos - imageManager.getImage(textureName).getSize().x / 2, yPos - imageManager.getImage(textureName).getSize().y / 2);
		break;
	default:
		throw std::invalid_argument("alignment only takes 0 or 1");
		break;
	}

	window.draw(sprite);
}

void Entity::animationUpdate(ImageManager imageManager)
	{
		if (animationFrame == 0)
		{
			sprite.setTexture(imageManager.getImage(currentAnimation + "0"));
		}

		else if (animationFrameTime >= animationMap[currentAnimation][animationFrame])
		{
			animationFrame=max(animationFrame+1, animationMap[currentAnimation].frameLengthArray.size());
			animationFrameTime = 0;
			sprite.setTexture(imageManager.getImage(currentAnimation + std::to_string(animationFrame)));
		}
		animationFrameTime += frameTime;
	}


void Entity::animationNew(std::string name)
{
	assert(animationMap.find(name) != animationMap.end());
	currentAnimation = name;
	animationFrameTime= 0;
	animationFrame = 0;
};