#include "player.h"

void Player::CheckInputs(std::map<int, bool> keyboardArray)
{
	//TODO could slightly refactor this to avoid the repetition
	if (m_actionState == actionState::idle)
	{
		if (keyboardArray[sf::Keyboard::W])
		{
			if (m_direction != 0) m_behaviourTriggers[directionChange] = true;
			m_direction = 0;
			m_behaviourTriggers[initiateMotion] = true;
		}
		else if (keyboardArray[sf::Keyboard::A])
		{
			if (m_direction != 1) m_behaviourTriggers[directionChange] = true;
			m_direction = 1;
			m_behaviourTriggers[initiateMotion] = true;
		}
		else if (keyboardArray[sf::Keyboard::S])
		{
			if (m_direction != 2) m_behaviourTriggers[directionChange] = true;
			m_direction = 2;
			m_behaviourTriggers[initiateMotion] = true;
		}
		else if (keyboardArray[sf::Keyboard::D])
		{
			if (m_direction != 3) m_behaviourTriggers[directionChange] = true;
			m_direction = 3;
			m_behaviourTriggers[initiateMotion] = true;
		}
		else if (keyboardArray[sf::Keyboard::Enter])
		{
			m_behaviourTriggers[useCard] = true;
		}
	}
	
	if (keyboardArray[sf::Keyboard::LControl])
	{
		m_behaviourTriggers[drawCardFromDeck] = true;
	}
	if (keyboardArray[sf::Keyboard::Left])
	{
		m_behaviourTriggers[selectCardLeft] = true;
	}
	else if (keyboardArray[sf::Keyboard::Right])
	{
		m_behaviourTriggers[selectCardRight] = true;
	}
}

void Player::Resize()
{
	//*cardPointsNumber.position = sf::Vector2f((float)(windowInfo.activeSceneWidthPixels + 4 * 32), (float)(windowInfo.getWindowHeight() - 32));
	//*healthNumber.position = sf::Vector2f((float)(windowInfo.activeSceneWidthPixels + 4 * 32), (float)(windowInfo.getWindowHeight() - 64));

	m_cardsInHand.resize();
}

void Player::Update(std::map<int, bool> keyboardArray, std::vector<std::vector<int>>& collision, int renderMode, CardActionMap& cardActionMap)
{
	//TODO see if you can remove this line
	m_battlingCharacterType->identifier = "player";

	ResetBehaviourTriggers();
	CheckInputs(keyboardArray);
	BattlingCharacter::Update(collision, renderMode, m_direction, cardActionMap);
	
	//CARDS

	if (renderMode == 1)
	{
		
		m_healthNumber.m_value = static_cast<int>(m_health);
		m_cardPointsNumber.m_value = static_cast<int>(m_cardPoints);
		int deckIndex=m_cardsInHand.action(this);

		if (m_behaviourTriggers[useCardSuccess])
		{
			cardActionMap.newAction(m_cardsInDeck.cardsInDeck[deckIndex], m_direction, m_currentTilePos,CharType::player, collision);
		}
	}
}

void Player::InitialiseBattleMode()
{
	m_cardsInDeck.resetDeck();
	m_cardsInHand.initialise(this);
	//*cardPointsNumber.position = sf::Vector2f(windowInfo.activeSceneWidthPixels + 3.5f * 32.0f, windowInfo.getWindowHeight() - 32.0f);
	//*healthNumber.position = sf::Vector2f(windowInfo.activeSceneWidthPixels + 3.5f * 32.0f, windowInfo.getWindowHeight() - 64.0f);
	BattlingCharacter::InitialiseBattleMode();
}

void Player::DrawToScreen(sf::RenderWindow& window)
{
	//cardPointsNumber.draw(window, Sprite::viewportSpace);
	//healthNumber.draw(window, Sprite::viewportSpace);
	m_cardsInHand.draw(window, this);
	BattlingCharacter::DrawToScreen(window);
}

