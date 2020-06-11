#include "AnimationManager.h"

void AnimationManager::updateAnimations(std::map<BehaviourTrigger, bool> behaviourTriggers, BattlingCharacterType* type, sf::Sprite& sprite)
{
	for (unsigned int i = 0; i < sizeof(playingAnimations); i++)
	{
		if (playingAnimations[i].timeActive > playingAnimations[i].animation->keyframes[playingAnimations[i].keyframeLocation].timePoint)
		{
			++playingAnimations[i].keyframeLocation;

		}
	}
}