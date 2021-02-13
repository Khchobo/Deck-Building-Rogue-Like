#include "Sprite.h"

void Sprite::initialise(PositionalEntity * _parent, std::string filename, PositionalEntity* componentParent, int centering)
{
	parent = _parent;
	sprite.setTexture(imageManager->getImage(filename + ".png"));
	textureSize = (imageManager->getImage(filename + ".png").getSize());
	if (centering == 0)
	{
		sprite.setOrigin(sf::Vector2f(imageManager->getImage(filename + ".png").getSize().x*static_cast<float>(0.5)
			, imageManager->getImage(filename + ".png").getSize().y*static_cast<float>(0.5)));
	}
	if (componentParent != _parent)
	{
		position = std::make_shared<sf::Vector2f>(componentParent->position);
	}
	else
	{
		position = std::make_shared<sf::Vector2f>(0, 0);
	}
}

void Sprite::draw(sf::RenderWindow& window, CoordSpace coordSpace)
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
		offset = sf::Vector2f(-static_cast<signed int>(textureSize.x) / 2 - windowInfo.backgroundTexturePosition.x, -static_cast<signed int>(textureSize.y) / 2 - windowInfo.backgroundTexturePosition.y);
		break;
	default:
		offset = sf::Vector2f(0, 0);
		break;
	}
	sprite.setPosition(offset.x+position->x + textureSize.x / 2+ windowInfo.backgroundTexturePosition.x, offset.y+position->y + textureSize.y / 2+ windowInfo.backgroundTexturePosition.y);
	window.draw(sprite);
}
