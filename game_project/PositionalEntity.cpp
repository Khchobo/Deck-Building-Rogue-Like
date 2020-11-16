#include "PositionalEntity.h"
#include "Sprite.h"

PositionalEntity::PositionalEntity(std::string identity, sf::Vector2f pos, ImageManager* imageManager) : Entity(identity, imageManager), position(pos) {}

PositionalEntity::PositionalEntity(std::string identity, ImageManager* imageManager) : Entity(identity, imageManager) {}

PositionalEntity::PositionalEntity(BattlingCharacterType* type, std::string identity, ImageManager* imageManager) : Entity(identity, imageManager)
{
	Sprite* sprite = new Sprite(this, imageManager, this->identity); //HOTFIX - Should swap this out with the file name eventually
	components.emplace_back(std::move(sprite));
}
