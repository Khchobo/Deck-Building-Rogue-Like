#include "PositionalEntity.h"
#include "Sprite.h"

PositionalEntity::PositionalEntity(BattlingCharacterType* type, std::string identity, ImageManager& imageManager) : Entity(identity, imageManager)
{
	Sprite* sprite = new Sprite();
	sprite->initialise(this);
	components.emplace_back(std::move(sprite));
}
