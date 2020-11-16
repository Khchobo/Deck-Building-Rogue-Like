#pragma once
#include "PositionalEntity.h"

class Sprite : public PositionalEntity
{
public:

	enum CoordSpace { localSpace,worldSpace,viewportSpace };

	Sprite() {}

	Sprite(PositionalEntity* _parent, ImageManager* imageManager, std::string filename = "", int centering = 0) : PositionalEntity(*_parent), parent(_parent), imageManager(imageManager) {	//using identity to define filepath is temporary till i can move sprite definitions into data
		identity = "Sprite";
		if (filename == "")
		{
			filename = identity;
		}
		initialise(_parent, filename, centering);
	}

	Sprite(PositionalEntity* _parent, std::string _identity, ImageManager* imageManager, std::string filename = "", int centering = 0) : PositionalEntity(*_parent), parent(_parent), imageManager(imageManager)
	{
		identity = _identity;
		if (filename == "")
		{
			filename = identity;
		}
		initialise(_parent, filename, centering);
	}

	PositionalEntity* parent;
	sf::Sprite sprite;
	sf::Texture texture;
	int centering = 0;

	void initialise(PositionalEntity* _parent, std::string filename, int centering = 0);

	virtual void draw(sf::RenderWindow& window, CoordSpace coordSpace = localSpace);

protected:
	sf::Vector2u textureSize;
private:

	std::string currentAnimation;
	ImageManager* imageManager;
	float animationFrameTime;
	int animationFrame;
};

