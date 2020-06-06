#include "player.h"

void Player::checkInputs(std::map<int, bool> keyboardArray)
{
	if (keyboardArray[sf::Keyboard::W])
	{
		direction = 0;
		behaviourTriggers[initiateMotion] = true;
	}
	else if (keyboardArray[sf::Keyboard::A])
	{
		direction = 1;
		behaviourTriggers[initiateMotion] = true;
	}
	else if (keyboardArray[sf::Keyboard::S])
	{
		direction = 2;
		behaviourTriggers[initiateMotion] = true;
	}
	else if (keyboardArray[sf::Keyboard::D])
	{
		direction = 3;
		behaviourTriggers[initiateMotion] = true;
	}
	if (keyboardArray[sf::Keyboard::LControl])
	{
		behaviourTriggers[drawCardFromDeck] = true;
	}
	else if (keyboardArray[sf::Keyboard::Enter])
	{
		behaviourTriggers[useCard] = true;
	}
	if (keyboardArray[sf::Keyboard::Left])
	{
		behaviourTriggers[selectCardLeft] = true;
	}
	else if (keyboardArray[sf::Keyboard::Right])
	{
		behaviourTriggers[selectCardRight] = true;
	}
}

void Player::resize(WindowInfo windowInfo)
{

	cardPointsNumber.xPos = windowInfo.activeSceneWidthPixels + 4 * 32;
	cardPointsNumber.yPos = windowInfo.getWindowHeight() - 32;

	cardsInHand.resize(windowInfo);
}

void Player::action(std::map<int, bool> keyboardArray, float& playerDistanceFromEdgeX, float& playerDistanceFromEdgeY,
	std::vector<std::vector<int>>& collision, WindowInfo windowInfo, int renderMode, CardActionMap& cardActionMap, ImageManager& imageManager)
{

	type->identifier = "player";
	resetBehaviourTriggers();
	checkInputs(keyboardArray);
	BattlingCharacter::action(collision,windowInfo, renderMode, direction);
	

	if (inMotion == 1)
	{
		//ensures the player stays bounded within the screen scroll static region
		playerDistanceFromEdgeX = min(max(static_cast<float>(200), playerDistanceFromEdgeX + distanceMovedX), static_cast<float>((windowInfo.activeSceneWidthPixels - windowInfo.tileSizeInPixels) - 200));
		playerDistanceFromEdgeY = min(max(static_cast<float>(200), playerDistanceFromEdgeY + distanceMovedY), static_cast<float>((windowInfo.activeSceneHeightPixels - windowInfo.tileSizeInPixels) - 200));
	}

	//CARDS

	if (renderMode == 1)
	{
		int cardIndex = 10000;

		cardPointsNumber.value = static_cast<int>(cardPoints);
		cardsInHand.action(type->identifier, cardsInDeck.cardsInDeck, cardsInDeck.cardsRemaining, windowInfo, cardIndex, cardPoints, behaviourTriggers, imageManager);

		if (cardIndex != 10000)
		{
			cardActionMap.newAction(cardIndex, cardsInDeck, direction, currentXTilePos, currentYTilePos, collision);
		}



	}

}

