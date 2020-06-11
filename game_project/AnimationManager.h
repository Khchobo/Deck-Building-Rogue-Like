#pragma once

#include "TransitionMap.h"
#include "StateAnimation.h"
#include "BehaviourTrigger.h"
#include "SquashAnimation.h"
#include "BattlingCharacterType.h"

struct PlayingAnimation
{
	PlayingAnimation() {}
	PlayingAnimation(std::string name, BattlingCharacterType* type) {
		animation = type->animationMap[name];
	}

	int keyframeLocation=-1;
	float timeActive = 0;
	std::shared_ptr<StateAnimation> animation;
};

class AnimationManager
{
public:
	AnimationManager(TransitionMap* transitions, BattlingCharacterType* type) : transitions(transitions)
	{
		playingAnimations[0] = PlayingAnimation(type->identifier + "defaultSquash", type);
	}

	void updateAnimations(std::map<BehaviourTrigger, bool> behaviourTriggers, BattlingCharacterType* type, sf::Sprite& sprite);

private:
	TransitionMap* transitions;
	//can only contain one of each animation type. currently this is 1 but need to increase this number as more are added.
	std::vector<PlayingAnimation> playingAnimations= std::vector<PlayingAnimation>(1);
};

