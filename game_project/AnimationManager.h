#pragma once

#include "entities\characters\BattlingCharacter.h"

struct PlayingAnimation
{
	PlayingAnimation(std::string name, BattlingCharacterType* type) {
		animation = type->animationMap[name];
	}

	void update() //need to overload with the various animation types
	{
		timeActive += frameTime;
		animation->updateAnimation(); //currently does nothing, need to overload 
	}

	float timeActive = 0;
	StateAnimation* animation;
};

class AnimationManager
{
public:
	void updateAnimations(std::map<BehaviourTrigger, bool> behaviourTriggers, BattlingCharacterType* type);

private:

};

