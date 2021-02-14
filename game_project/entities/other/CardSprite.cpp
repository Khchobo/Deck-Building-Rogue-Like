#include "CardSprite.h"
#include <iostream>
#include "globalVariables.h"
#include "CardsInHand.h"

void CardSprite::UpdateCardMotion(int index)
{
		//state transitions upon completed movements
		if (motionPercentage == 1)
		{
			motionPercentage = 0;
			inMotion = 0;

			if (locationState == CardLocationState::New || locationState ==CardLocationState::BecomingUnselected)
			{
				int formerPos = locationState;
				locationState = CardLocationState::Unselected;

				if (dynamic_cast<CardsInHand*>(m_pParentObject)->GetSelectedCard() == index && formerPos== CardLocationState::New)
				{
					SetState(CardLocationState::BecomingSelected);
				}
			}
			else if (locationState == CardLocationState::BelowUsedBecomingSelected)
			{
				locationState = CardLocationState::Selected;
			}
			else if (locationState == CardLocationState::BelowUsedNotBecomingSelected)
			{
				locationState = CardLocationState::Unselected;
			}
			else if (locationState == CardLocationState::BecomingSelected)
			{
				locationState == CardLocationState::Selected;
			}

			return;
		}

		if (runTime != 0)
		{
			motionPercentage += frameTime / motionTime;
		}

		//prevents motions overshooting
		if (motionPercentage > 1)
		{
			motionPercentage = 1;
		}

		switch (locationState) {
		case(CardLocationState::BecomingSelected):
		{
			position.y = previousPos.y - (standaloneFunctions::easeInOut(motionPercentage) * 32);
			break;
		}
		case(CardLocationState::BecomingUnselected):
		{
			position.y = previousPos.y + (standaloneFunctions::easeInOut(motionPercentage) * 32);
			break;
		}
		case(CardLocationState::New):
			position.x = (previousPos.x* (1 - standaloneFunctions::easeInOut(motionPercentage)) + (index * 32)*( (standaloneFunctions::easeInOut(motionPercentage))));
			if (windowInfo.fullscreen == 0) 
			{ 
				position.y = previousPos.y * (1- standaloneFunctions::easeInOut(motionPercentage)) + ((windowInfo.activeSceneHeightTiles + 1) * 32)*(standaloneFunctions::easeInOut(motionPercentage));
			}
			else { 
				position.y = previousPos.y*(1- standaloneFunctions::easeInOut(motionPercentage)) + (sf::VideoMode::getDesktopMode().height - (windowInfo.UIHeight - 1) * 32)*(standaloneFunctions::easeInOut(motionPercentage));
			}
		case(CardLocationState::BelowUsedNotBecomingSelected):
			position.x = (previousPos.x* (1 - standaloneFunctions::easeInOut(motionPercentage)) + (index * 32)*((standaloneFunctions::easeInOut(motionPercentage))));
			
			break;
		case(CardLocationState::BelowUsedBecomingSelected):
			position.x = (previousPos.x* (1 - standaloneFunctions::easeInOut(motionPercentage)) + (index * 32)*((standaloneFunctions::easeInOut(motionPercentage))));
			position.y = previousPos.y - (standaloneFunctions::easeInOut(motionPercentage) * 32);
		default:
			break;
		}

}

void CardSprite::SetState(CardLocationState state)
{
	locationState = state;
	inMotion = true;
	previousPos = position;
	//movements from CardLocationState::New take longer
	if (locationState == CardLocationState::New)
	{
		motionTime = 0.55f;
	}
	else {
		motionTime = 0.225f;
	}
}

CardSprite::CardLocationState CardSprite::GetState()
{
	return locationState;
}