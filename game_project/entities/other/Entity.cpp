#include "Entity.h"

//alignmentMode is whether to position relative to the top right corner or the middle of the texture.
void Entity::initialise(std::string fileName,sf::Vector2f incomingPosition,bool alignmentMode,ImageManager& imageManager)
{
	
	alignment = alignmentMode;

	sprite.setTexture(imageManager.getImage(fileName)); 
	
	textureSize = (imageManager.getImage(fileName).getSize());
	position = incomingPosition;

}

void Entity::draw(sf::RenderWindow& window,ImageManager& imageManager)
{
	switch (alignment)
	{
	case(0):
		sprite.setPosition(position);
		break;
	case(1):
		sprite.setPosition(position.x - textureSize.x / 2, position.y - textureSize.y / 2);
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