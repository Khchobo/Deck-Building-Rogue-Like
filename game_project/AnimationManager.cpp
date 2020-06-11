#include "AnimationManager.h"

void AnimationManager::updateAnimations(std::map<BehaviourTrigger, bool> behaviourTriggers, BattlingCharacterType* type, sf::Sprite& sprite)
{
	for (unsigned int i = 0; i < playingAnimations.size(); i++)
	{
		if (runTime > 0)
		{
			playingAnimations[i].timeActive += frameTime;
		}

		Keyframe currentKeyframe= playingAnimations[i].animation->keyframes[playingAnimations[i].keyframeLocation];

		//check if we have moved to the next keyframe
		if (playingAnimations[i].timeActive >= playingAnimations[i].animation->keyframes[playingAnimations[i].keyframeLocation+1].timePoint)
		{
			playingAnimations[i].keyframeLocation++;
			currentKeyframe = playingAnimations[i].animation->keyframes[playingAnimations[i].keyframeLocation];
		}

		//trigger repeats and behaviours if applicable
		if (currentKeyframe.behaviourTrigger != null)
		{
			behaviourTriggers[currentKeyframe.behaviourTrigger] = true;
		}

		if (currentKeyframe.repeatTrigger != -1.0f)
		{
			playingAnimations[i].timeActive = currentKeyframe.repeatTrigger;
			for (int j=0; j<playingAnimations[i].animation->keyframes.size();j++)
			{
				if (playingAnimations[i].animation->keyframes[j].timePoint > currentKeyframe.repeatTrigger)
				{
					playingAnimations[i].keyframeLocation = j - 1;
					break;
				}
			}
		}


		//the transitions possible from the current animation
		std::map<BehaviourTrigger, std::string> currentAnimationTransistions = transitions->operator[](playingAnimations[i].animation->name);

		//for each possible transition from the current animation
		for (std::map<BehaviourTrigger, std::string>::iterator iter = currentAnimationTransistions.begin(); iter != currentAnimationTransistions.end(); ++iter)
		{
			//if the trigger is active
			if (behaviourTriggers[iter->first])
			{
				//trigger the animation
				playingAnimations[i] = PlayingAnimation(iter->second, type);
			}
		}

		//update the animation
		playingAnimations[i].animation->update(playingAnimations[i].timeActive, playingAnimations[i].keyframeLocation, sprite);

	}


}