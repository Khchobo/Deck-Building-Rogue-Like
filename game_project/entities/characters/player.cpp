#include "player.h"

void Player::checkInputs(std::map<int, bool> keyboardArray)
{
	//TODO could slightly refactor this to avoid the repetition
	if (state == actionState::idle)
	{
		if (keyboardArray[sf::Keyboard::W])
		{
			if (direction != 0) behaviourTriggers[directionChange] = true;
			direction = 0;
			behaviourTriggers[initiateMotion] = true;
		}
		else if (keyboardArray[sf::Keyboard::A])
		{
			if (direction != 1) behaviourTriggers[directionChange] = true;
			direction = 1;
			behaviourTriggers[initiateMotion] = true;
		}
		else if (keyboardArray[sf::Keyboard::S])
		{
			if (direction != 2) behaviourTriggers[directionChange] = true;
			direction = 2;
			behaviourTriggers[initiateMotion] = true;
		}
		else if (keyboardArray[sf::Keyboard::D])
		{
			if (direction != 3) behaviourTriggers[directionChange] = true;
			direction = 3;
			behaviourTriggers[initiateMotion] = true;
		}
		else if (keyboardArray[sf::Keyboard::Enter])
		{
			behaviourTriggers[useCard] = true;
		}
	}
	
	if (keyboardArray[sf::Keyboard::LControl])
	{
		behaviourTriggers[drawCardFromDeck] = true;
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

	cardPointsNumber.position = sf::Vector2f(windowInfo.activeSceneWidthPixels + 4 * 32, windowInfo.getWindowHeight() - 32);
	healthNumber.position = sf::Vector2f(windowInfo.activeSceneWidthPixels + 4 * 32, windowInfo.getWindowHeight() - 64);

	cardsInHand.resize(windowInfo);
}

void Player::action(std::map<int, bool> keyboardArray, float& playerDistanceFromEdgeX, float& playerDistanceFromEdgeY,
	std::vector<std::vector<int>>& collision, WindowInfo windowInfo, int renderMode, CardActionMap& cardActionMap, ImageManager& imageManager)
{
	//TODO see if you can remove this line
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
		healthNumber.value = static_cast<int>(health);
		cardPointsNumber.value = static_cast<int>(cardPoints);
		cardsInHand.action(type->identifier, cardsInDeck.cardsInDeck, cardsInDeck.cardsRemaining, windowInfo, cardIndex, cardPoints, behaviourTriggers, imageManager);

		if (cardIndex != 10000)
		{
			cardActionMap.newAction(cardIndex, cardsInDeck, direction, currentTilePos, collision);
		}



	}

}

