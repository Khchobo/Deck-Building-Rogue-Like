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

	virtual void draw(sf::RenderWindow& window,const WindowInfo& windowInfo, CoordSpace coordSpace = localSpace, const PositionalEntity* parent=&PositionalEntity());

	void initialise(const Entity* parent, sf::Vector2f offset = sf::Vector2f(0, 0));
protected:
	sf::Vector2u textureSize;
private:

	std::string currentAnimation;

	float animationFrameTime;
	int animationFrame;
};

