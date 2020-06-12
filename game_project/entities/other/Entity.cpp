#include "Entity.h"

//alignmentMode is whether to position relative to the top right corner or the middle of the texture.
void Entity::initialise(std::string fileName,sf::Vector2f incomingPosition,ImageManager& imageManager)
{
	sprite.setTexture(imageManager.getImage(fileName)); 
	
	textureSize = (imageManager.getImage(fileName).getSize());
	sprite.setOrigin(sf::Vector2f(imageManager.getImage(fileName).getSize().x*static_cast<float>(0.5)
								, imageManager.getImage(fileName).getSize().y*static_cast<float>(0.5)));
	position = incomingPosition;

}

void Entity::draw(sf::RenderWindow& window)
{
	sprite.setPosition(position.x + textureSize.x / 2, position.y + textureSize.y / 2);
	window.draw(sprite);
}
