#include "Sprite.h"

void Sprite::initialise(Entity* _parentObject, Entity* _rootObject, std::string filename, int centering)
{
	parentObject = _parentObject;
	rootObject = _rootObject;
	sprite.setTexture(imageManager->getImage(filename + ".png"));
	textureSize = (imageManager->getImage(filename + ".png").getSize());
	if (centering == 0)
	{
		sprite.setOrigin(sf::Vector2f(imageManager->getImage(filename + ".png").getSize().x*static_cast<float>(0.5)
			, imageManager->getImage(filename + ".png").getSize().y*static_cast<float>(0.5)));
	}
}

void Sprite::draw(sf::RenderWindow& window, CoordSpace coordSpace)
{
	PositionalEntity* pPositionalEntity = dynamic_cast<PositionalEntity*>(parentObject);
	sf::Vector2f position =sf::Vector2f(0,0);
	switch (coordSpace)
	{
	case(localSpace):
	{
		PositionalEntity* pWorkingObject = pPositionalEntity;
		do
		{
			position = sf::Vector2f(pWorkingObject->position.x + position.x, pWorkingObject->position.y + position.y);
			pWorkingObject = static_cast<PositionalEntity*>(pWorkingObject->parentObject);
		} while (pWorkingObject != rootObject);
		break;
	}
	case(worldSpace):
		position = sf::Vector2f(0, 0);
		break;
	case(viewportSpace):
		position = sf::Vector2f(pPositionalEntity->position.x-static_cast<signed int>(textureSize.x) / 2 - windowInfo.backgroundTexturePosition.x,
								pPositionalEntity->position.y-static_cast<signed int>(textureSize.y) / 2 - windowInfo.backgroundTexturePosition.y);
		break;
	default:
		assert(false);
		break;
	}
	sprite.setPosition(position.x + textureSize.x / 2+ windowInfo.backgroundTexturePosition.x, position.y + textureSize.y / 2+ windowInfo.backgroundTexturePosition.y);
	window.draw(sprite);
}
