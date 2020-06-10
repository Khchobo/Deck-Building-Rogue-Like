#pragma once

#include <vector>
#include <Keyframe.h>

class StateAnimation
{
public:
	std::vector<Keyframe> keyframes;
	virtual void updateAnimation()=0;

};

