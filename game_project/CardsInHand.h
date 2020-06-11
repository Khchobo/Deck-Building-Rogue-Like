#pragma once
#include <vector>
#include <iostream>
#include <stdlib.h>
#include "Card.h"
#include "entities\other\CardSprite.h"
#include "entities\other\NumberEntity.h"
#include "WindowInfo.h"
#include "globalVariables.h"
#include "BehaviourTrigger.h"
#include <string>

static class CardsInHand: public Entity
{
public:

	CardsInHand(){}

	CardsInHand(int x) : cardsInHand(x)
	{
		selected = rand() % x;
		cardsInHand[selected].movementLocation = 1;
		cardsInHand[selected].offset = 1;
	}

	void initialise(std::vector<Card>& cardsInDeck, std::vector<long double>& cardsRemaining, WindowInfo windowInfo, std::string identifier, ImageManager& imageManager);

	void draw(sf::RenderWindow &window, std::vector<Card>& cardsInDeck, ImageManager& imageManager);

	void resize(WindowInfo windowInfo);

	void action(std::string identifier, std::vector<Card>& cardsInDeck,
				std::vector<long double>& cardsRemaining, WindowInfo windowInfo, int& cardIndex,
				float& cardPoints, std::map<BehaviourTrigger, bool> behaviourTriggers, ImageManager& imageManager);

	void drawCard(std::vector<Card>& cardsInDeck, std::vector<long double>& cardsRemaining,std::string identifier,ImageManager& imageManager);

	void newMotion(int index);

	void cardInfoPrint(std::vector<Card>& cardsInDeck);

	void cardInfoDraw(std::vector<Card>& cardsInDeck, sf::RenderWindow& window);

	bool anyCardsInMotion(std::vector<CardSprite> cardsInHand);

	void changeSelection(unsigned int& selected, std::string identifier, std::vector<CardSprite> cardsInHand,
							std::map<BehaviourTrigger, bool> behaviourTriggers, std::vector<Card>& cardsInDeck);

	std::vector<CardSprite> cardsInHand;

private:

	std::map<AttackType,std::string> attackTypeMap = {{AttackType::circle, "Circle"}, { AttackType::line,"Line" },{AttackType::cross,"Cross"} };

	sf::Text text;
	sf::Font font;

	Entity deckSprite;
	NumberEntity noOfCardsInHand;
	unsigned int selected;
	int drawCardCooldown = 10;
};

