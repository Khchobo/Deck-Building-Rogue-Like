#include "SquashAnimation.h"

void SquashAnimation::update(float& timeActive, int& keyframeLocation, sf::Sprite& sprite)
{
	//linear interpolation between current keyframe and the next one
	//(1-p)*x+p*y where p=(t-t_x)/(t_y-t_x)
	float percentage = (timeActive - keyframes[keyframeLocation].timePoint) / (keyframes[keyframeLocation + 1].timePoint - keyframes[keyframeLocation].timePoint);
	float scaleX = (1.0f - percentage)*keyframes[keyframeLocation].vector.x + percentage * keyframes[keyframeLocation + 1].vector.x;
	float scaleY= (1.0f - percentage)*keyframes[keyframeLocation].vector.y + percentage * keyframes[keyframeLocation + 1].vector.y;
	sf::Vector2f scale = sf::Vector2f(scaleX, scaleY);

	sprite.setScale(scale);
}