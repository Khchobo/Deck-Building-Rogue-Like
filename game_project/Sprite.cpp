#include "Sprite.h"

void Sprite::initialise(const Entity* parent, sf::Vector2f offset)
{

	//using identity to define filepath is temporary till i can move sprite definitions into data
	sprite.setTexture(parent->imageManager->getImage(parent->identity+".png"));
	identity = "Sprite";
	textureSize = (parent->imageManager->getImage(parent->identity + ".png").getSize());
	sprite.setOrigin(sf::Vector2f(parent->imageManager->getImage(parent->identity + ".png").getSize().x*static_cast<float>(0.5)
		, parent->imageManager->getImage(parent->identity + ".png").getSize().y*static_cast<float>(0.5)));
	position = offset;

}

void Sprite::draw(sf::RenderWindow& window,const WindowInfo& windowInfo, const PositionalEntity* parent, CoordSpace coordSpace)
{
	sf::Vector2f offset;
	switch (coordSpace)
	{
	case(localSpace):
		offset = parent->position;
		break;
	case(worldSpace):
		offset = sf::Vector2f(0, 0);
		break;
	case(viewportSpace):
		assert(false); //todo
		break;
	default:
		offset = sf::Vector2f(0, 0);
		break;
	}
	sprite.setPosition(offset.x+position.x + textureSize.x / 2+ windowInfo.backgroundTexturePosition.x, offset.y+position.y + textureSize.y / 2+ windowInfo.backgroundTexturePosition.y);
	window.draw(sprite);
}
