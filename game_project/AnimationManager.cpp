#include "AnimationManager.h"

void AnimationManager::updateAnimations(std::map<BehaviourTrigger, bool> behaviourTriggers, BattlingCharacterType* type, sf::Sprite& sprite)
{
	for (unsigned int i = 0; i < sizeof(playingAnimations); i++)
	{
		playingAnimations[i].timeActive += frameTime;

		Keyframe currentKeyframe = playingAnimations[i].animation->keyframes[playingAnimations[i].keyframeLocation];

		if (playingAnimations[i].timeActive >= currentKeyframe.timePoint)
		{
			playingAnimations[i].keyframeLocation++;
			currentKeyframe = playingAnimations[i].animation->keyframes[playingAnimations[i].keyframeLocation];
		}

		if (currentKeyframe.repeatTrigger != NAN)
		{
			playingAnimations[i].timeActive = currentKeyframe.repeatTrigger;
		}

		if (currentKeyframe.behaviourTrigger != null)
		{
			behaviourTriggers[currentKeyframe.behaviourTrigger] = true;
		}

		//TODO at this point handle animation transitions

		playingAnimations[i].animation->update(playingAnimations[i].timeActive, playingAnimations[i].keyframeLocation, sprite);

	}


}