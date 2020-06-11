#pragma once

#include <string>
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

//Largely an abstract class representing some keyframe data. Identifier, vector and colour may be interpreted differently depending on
//what type of keyframeableState the keyframe is a part of. However timePoint will be used in all keyframes and denotes how much time 
//in seconds has passed between the beginning of the animation state and this keyframe. Trigger is used to set off a behaviour trigger.
class Keyframe
{
public:

	Keyframe(float timePoint, std::string identifier) : timePoint(timePoint), identifier(identifier){}
	Keyframe(float timePoint, sf::Vector2f vector) : timePoint(timePoint), vector(vector) {}
	Keyframe(float timePoint, sf::Color colour) : timePoint(timePoint), colour(colour) {}

	float timePoint;
	std::string identifier;
	sf::Vector2f vector;
	sf::Color colour;
	BehaviourTrigger trigger;
};

