#include "PositionalEntity.h"
#include "Sprite.h"

PositionalEntity::PositionalEntity(std::string identity, sf::Vector2f pos, ImageManager* imageManager,
	std::string filename, Entity* parentObject, Entity* rootObject, int spriteCentering) :
	Entity(identity, imageManager, parentObject, rootObject), position(pos)
{
	components.emplace_back(std::make_shared<Sprite>((Entity*)this, rootObject, imageManager, filename, spriteCentering));
}

PositionalEntity::PositionalEntity(std::string identity, ImageManager* imageManager,
	std::string filename, Entity* parentObject, Entity* rootObject, int spriteCentering) :
	Entity(identity, imageManager, parentObject, rootObject)
{
	components.emplace_back(std::make_shared<Sprite>((Entity*)this, rootObject, imageManager, filename, spriteCentering));
}
