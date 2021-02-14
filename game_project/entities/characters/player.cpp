#include "player.h"

void Player::checkInputs(std::map<int, bool> keyboardArray)
{
	//TODO could slightly refactor this to avoid the repetition
	if (actionstate == actionState::idle)
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

void Player::resize()
{
	//*cardPointsNumber.position = sf::Vector2f((float)(windowInfo.activeSceneWidthPixels + 4 * 32), (float)(windowInfo.getWindowHeight() - 32));
	//*healthNumber.position = sf::Vector2f((float)(windowInfo.activeSceneWidthPixels + 4 * 32), (float)(windowInfo.getWindowHeight() - 64));

	cardsInHand.resize();
}

void Player::action(std::map<int, bool> keyboardArray, std::vector<std::vector<int>>& collision, int renderMode, CardActionMap& cardActionMap)
{
	//TODO see if you can remove this line
	type->identifier = "player";

	resetBehaviourTriggers();
	checkInputs(keyboardArray);
	BattlingCharacter::action(collision, renderMode, direction, cardActionMap);
	
	//CARDS

	if (renderMode == 1)
	{
		
		healthNumber.value = static_cast<int>(health);
		cardPointsNumber.value = static_cast<int>(cardPoints);
		int deckIndex=cardsInHand.action(this);

		if (behaviourTriggers[useCardSuccess])
		{
			cardActionMap.newAction(cardsInDeck.cardsInDeck[deckIndex], direction, currentTilePos,CharType::player, collision);
		}
	}
}

void Player::initialiseBattleMode()
{
	cardsInDeck.resetDeck();
	cardsInHand.initialise(this);
	//*cardPointsNumber.position = sf::Vector2f(windowInfo.activeSceneWidthPixels + 3.5f * 32.0f, windowInfo.getWindowHeight() - 32.0f);
	//*healthNumber.position = sf::Vector2f(windowInfo.activeSceneWidthPixels + 3.5f * 32.0f, windowInfo.getWindowHeight() - 64.0f);
	BattlingCharacter::initialiseBattleMode();
}

void Player::draw(sf::RenderWindow& window)
{
	//cardPointsNumber.draw(window, Sprite::viewportSpace);
	//healthNumber.draw(window, Sprite::viewportSpace);
	cardsInHand.draw(window, this);
	BattlingCharacter::draw(window);
}

