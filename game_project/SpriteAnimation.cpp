#include "SpriteAnimation.h"

Animation::SpriteAnimation() {}

Animation::SpriteAnimation(std::string name, unsigned int length, std::vector<int> frameLengthArray) : name(name), length(length), frameLengthArray(frameLengthArray)
{
}
