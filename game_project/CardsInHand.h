#pragma once
#include <vector>
#include <iostream>
#include <stdlib.h>
#include "Card.h"
#include "entities\other\CardSprite.h"
#include "entities\other\NumberEntity.h"

#include "Sprite.h"
#include "WindowInfo.h"
#include "globalVariables.h"
#include "BehaviourTrigger.h"
#include <string>

class BattlingCharacter;
class CardsInHand: public Entity
{
public:

	CardsInHand(){}

	CardsInHand(int x) : cardsInHand(x)
	{
		selected = rand() % x;
		cardsInHand[selected].movementLocation = 1;
		cardsInHand[selected].offset = 1;
	}

	void initialise(BattlingCharacter* parent, const WindowInfo& windowInfo);

	void draw(sf::RenderWindow &window, const Entity* parent, WindowInfo& windowInfo);

	void resize(WindowInfo windowInfo);

	int action(BattlingCharacter* parent, WindowInfo windowInfo);

	void drawCard(BattlingCharacter* parent);

	void newMotion(int index);

	void cardInfoPrint(std::vector<Card>& cardsInDeck);

	void cardInfoDraw(const std::vector<Card>& cardsInDeck, sf::RenderWindow& window);

	bool anyCardsInMotion(std::vector<CardSprite> cardsInHand);

	void changeSelection(unsigned int& selected, std::string identifier, std::vector<CardSprite> cardsInHand,
							std::map<BehaviourTrigger, bool> behaviourTriggers, std::vector<Card>& cardsInDeck);

	std::vector<CardSprite> cardsInHand;

private:

	std::map<AttackType,std::string> attackTypeMap = {{AttackType::circle, "Circle"}, { AttackType::line,"Line" },{AttackType::cross,"Cross"} };

	sf::Text text;
	sf::Font font;

	Sprite deckSprite;
	NumberEntity noOfCardsInHand;
	unsigned int selected;
	int drawCardCooldown = 10;
};

