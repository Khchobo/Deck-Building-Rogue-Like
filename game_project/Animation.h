#pragma once
#include <string>
#include <vector>
/**
*Stores the name of an animation and an array of each how long each sprite in the animation should last in frames.
*The name of the animation is directly used to access the animation from the relevant folder directory.
*TODO eventually these will be initiliased from data files.
*/
class Animation
{
public:
	Animation();
	Animation(std::string name, unsigned int length, std::vector<int> frameLengthArray);

	std::string name;
	unsigned int length;

	int operator[](int i) { return frameLengthArray[i];}

	//vector which stores how many frames each sprite in the animation lasts
	std::vector<int> frameLengthArray;
};

