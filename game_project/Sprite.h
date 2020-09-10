#pragma once
#include "PositionalEntity.h"
#include "WindowInfo.h"

class Sprite : public PositionalEntity
{
public:

	enum CoordSpace { localSpace,worldSpace,viewportSpace };


	Sprite() : PositionalEntity() {}

	sf::Sprite sprite;
	sf::Texture texture;

	void draw(sf::RenderWindow& window,const WindowInfo& windowInfo, const PositionalEntity* parent=&PositionalEntity(), CoordSpace coordSpace = localSpace);

	void initialise(const Entity* parent, sf::Vector2f offset = sf::Vector2f(0, 0));


private:

	sf::Vector2u textureSize;
	std::string currentAnimation;

	float animationFrameTime;
	int animationFrame;
};

