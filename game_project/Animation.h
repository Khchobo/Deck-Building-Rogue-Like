#pragma once
#include <string>
#include <vector>
class Animation
{
public:
	Animation(std::string name, unsigned int length, std::vector<int> frameLengthArray);

	std::string name;
	unsigned int length;

	//vector which stores how many frames each sprite in the animation lasts
	std::vector<int> frameLengthArray;
};

