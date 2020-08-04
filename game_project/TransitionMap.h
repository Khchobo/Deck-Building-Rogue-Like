#pragma once
#include<string>
#include <map>
#include "BehaviourTrigger.h"

struct TransitionMap
{
	std::map<BehaviourTrigger, std::string>& operator[](std::string string)
	{
		return map[string];
	}

	std::map<std::string, std::map<BehaviourTrigger, std::string>> map;
};

