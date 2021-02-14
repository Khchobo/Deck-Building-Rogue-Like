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
		m_identity = "Sprite";
		if (filename == "")
		{
			filename = m_identity;
		}
		Initialise(parentObject, rootObject, filename, centering);
	}

	Sprite(Entity* parentObject, Entity* rootObject, std::string _identity, ImageManager* imageManager, std::string filename = "", int centering = 0)
		: Entity(filename, imageManager, parentObject, rootObject)
	{
		m_identity = _identity;
		if (filename == "")
		{
			filename = m_identity;
		}
	Initialise(parentObject, rootObject, filename, centering);
	}

	void Initialise(Entity* _parentObject, Entity* _rootObject, std::string filename, int centering = 0);
	virtual void DrawToScreen(sf::RenderWindow& window, CoordSpace coordSpace = localSpace);

	sf::Sprite m_sprite;
	sf::Texture m_texture;
	int m_centering = 0;

protected:
	sf::Vector2u m_textureSize;
private:

	std::string m_currentAnimation;
	float m_animationFrameTime;
	int m_animationFrame;
};

