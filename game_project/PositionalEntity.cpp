#include "PositionalEntity.h"
#include "Sprite.h"

PositionalEntity::PositionalEntity(std::string identity, sf::Vector2f pos, ImageManager* imageManager, std::string filename, PositionalEntity* parent, int spriteCentering) : Entity(identity, imageManager), position(pos)
{
	std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>(parent, imageManager, this, filename, spriteCentering);
	components.emplace_back(std::move(sprite));
}

PositionalEntity::PositionalEntity(std::string identity, ImageManager* imageManager, std::string filename, PositionalEntity* parent, int spriteCentering) : Entity(identity, imageManager)
{
	std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>(parent, imageManager, this, filename, spriteCentering);
	components.emplace_back(std::move(sprite));
}
