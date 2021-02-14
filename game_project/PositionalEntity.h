#pragma once
#include "entities\other\Entity.h"
#include "BattlingCharacterType.h"


class Sprite;

class PositionalEntity : public Entity
{
public:

	PositionalEntity(std::string identity, sf::Vector2f pos, ImageManager* imageManager, std::string filename,
		Entity* parentObject, Entity* rootObject, int spriteCentering = 0);
	PositionalEntity(std::string identity, ImageManager* imageManager, std::string filename,
		Entity* parentObject, Entity* rootObject, int spriteCentering = 0);

	void Initialise() override;
	void Update() override;

	sf::Vector2f position;

};

