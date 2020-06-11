#pragma once

#include <vector>
#include <Keyframe.h>

enum class animType { sprite, squash };


struct StateAnimation
{
public:
	std::vector<Keyframe> keyframes;
	virtual void update(float& timeActive, int& keyframeLocation,sf::Sprite& sprite) = 0; //TODO also need to add some kind of struct to hold shader data

	
};

