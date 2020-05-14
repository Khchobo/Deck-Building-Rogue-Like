#include "Animation.h"

Animation::Animation() {}

Animation::Animation(std::string name, unsigned int length, std::vector<int> frameLengthArray) : name(name), length(length), frameLengthArray(frameLengthArray)
{
}
