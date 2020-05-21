#include "player.h"

bool Player::checkForMotion(std::map<int, bool> keyboardArray)
{
	bool flag = false;
	if (keyboardArray[sf::Keyboard::W])
	{
		direction = 0;
		flag = true;
	}
	else if (keyboardArray[sf::Keyboard::A])
	{
		direction = 1;
		flag = true;
	}
	else if (keyboardArray[sf::Keyboard::S])
	{
		direction = 2;
		flag = true;
	}
	else if (keyboardArray[sf::Keyboard::D])
	{
		direction = 3;
		flag = true;
	}
	return flag;
}

void Player::resize(WindowInfo windowInfo)
{

	cardPointsNumber.xPos = windowInfo.activeSceneWidthPixels + 4 * 32;
	cardPointsNumber.yPos = windowInfo.getWindowHeight() - 32;

	cardsInHand.resize(windowInfo);
}

void Player::action(std::map<int, bool> keyboardArray, float& playerDistanceFromEdgeX, float& playerDistanceFromEdgeY,
	std::vector<std::vector<int>>& collision, WindowInfo windowInfo, int renderMode, CardActionMap& cardActionMap)
{
	//PLAYER MOTION

	bool flag=checkForMotion(keyboardArray);
	
	if (flag && cardPoints>cardPointsStepCost && !(inMotion))
	{
		initiateNewMotion(direction, collision);
	}

	if (inMotion == 1)
	{
		updateMotion(windowInfo);

		//ensures the player stays bounded within the screen scroll static region
		playerDistanceFromEdgeX = min(max(static_cast<float>(80),playerDistanceFromEdgeX+distanceMovedX), static_cast<float>((windowInfo.activeSceneWidthPixels-windowInfo.tileSizeInPixels) - 80));
		playerDistanceFromEdgeY = min(max(static_cast<float>(80), playerDistanceFromEdgeY + distanceMovedY), static_cast<float>((windowInfo.activeSceneWidthPixels - windowInfo.tileSizeInPixels) - 80));
	}

	//CARDS

	if (renderMode == 1)
	{
		int cardIndex = 10000;

		cardPoints = min(static_cast<float>(type.cardPointsMax), cardPoints + type.cardPointRecoveryRate*frameTime);

		cardPointsNumber.value = static_cast<int>(cardPoints);

		cardsInHand.action(keyboardArray, cardsInDeck.cardsInDeck, cardsInDeck.cardsRemaining, windowInfo, cardIndex, cardPoints);

		if (cardIndex != 10000)
		{
			cardActionMap.newAction(cardIndex, cardsInDeck, direction, currentXTilePos, currentYTilePos, collision);
		}


		
	}

}

void Player::draw(sf::RenderWindow& window, float backgroundXPos, float backgroundYPos)
{
	sprite.setTexture(texture);
	sprite.setPosition(xPos + backgroundXPos, yPos + backgroundYPos);
	window.draw(sprite);
}