#pragma once
#include "PositionalEntity.h"

class Sprite : public Entity
{
public:

	enum CoordSpace { localSpace,worldSpace,viewportSpace };

	Sprite() {}

	Sprite(Entity* parentObject, Entity* rootObject, ImageManager* imageManager, std::string filename = "", int centering = 0)
		 : Entity(filename, imageManager, parentObject, rootObject) {	
		//using identity to define filepath is temporary till i can move sprite definitions into data
		identity = "Sprite";
		if (filename == "")
		{
			filename = identity;
		}
		initialise(parentObject, rootObject, filename, centering);
	}

	Sprite(Entity* parentObject, Entity* rootObject, std::string _identity, ImageManager* imageManager, std::string filename = "", int centering = 0)
		: Entity(filename, imageManager, parentObject, rootObject)
	{
		identity = _identity;
		if (filename == "")
		{
			filename = identity;
		}
	initialise(parentObject, rootObject, filename, centering);
	}

	sf::Sprite sprite;
	sf::Texture texture;
	int centering = 0;

	void initialise(Entity* _parentObject, Entity* _rootObject, std::string filename, int centering = 0);

	virtual void draw(sf::RenderWindow& window, CoordSpace coordSpace = localSpace);

protected:
	sf::Vector2u textureSize;
private:

	std::string currentAnimation;
	float animationFrameTime;
	int animationFrame;
};

