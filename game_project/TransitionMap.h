#pragma once
#include<string>
#include<unordered_map>
#include "entities/characters/BattlingCharacter.h"

struct TransitionMap
{
	std::unordered_map<BehaviourTrigger, std::string>& operator[](std::string string)
	{
		return map[string];
	}

	std::unordered_map<std::string, std::unordered_map<BehaviourTrigger, std::string>> map;
};

