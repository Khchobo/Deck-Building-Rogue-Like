#pragma once

#include "TransitionMap.h"
#include "StateAnimation.h"
#include "entities/other/Entity.h"
#include "SquashAnimation.h"
#include "BattlingCharacterType.h"
#include "entities/characters/BattlingCharacter.h"

struct PlayingAnimation
{
	PlayingAnimation() {}
	PlayingAnimation(std::string name, BattlingCharacterType* type) {
		animation = type->animationMap[name];
	}

	int keyframeLocation=0;
	float timeActive = 0;
	std::shared_ptr<StateAnimation> animation;
};

class AnimationManager : public Entity
{
public:

	AnimationManager(){}

	void initalise(BattlingCharacterType* type)
	{
		identity = "AnimationManager";
		transitions = &type->animationTransitions;
		playingAnimations[0] = PlayingAnimation("defaultSquash", type);
	}

	void update(BattlingCharacter* parent);

	void updateAnimations(std::map<BehaviourTrigger, bool> behaviourTriggers, BattlingCharacterType* type, Sprite* sprite);

private:
	TransitionMap* transitions;
	//can only contain one of each animation type. currently this is 1 but need to increase this number as more are added.
	std::vector<PlayingAnimation> playingAnimations= std::vector<PlayingAnimation>(1);
};

