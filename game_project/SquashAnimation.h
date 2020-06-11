#pragma once
#include "StateAnimation.h"
class SquashAnimation :
	public StateAnimation
{
public:
	void update(float& timeActive, int& keyframeLocation,sf::Sprite& sprite);
};

