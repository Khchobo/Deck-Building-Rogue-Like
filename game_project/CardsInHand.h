#pragma once
#include <vector>
#include <iostream>
#include <stdlib.h>
#include "Card.h"
#include "entities\other\CardSprite.h"
#include "entities\other\NumberEntity.h"

#include "Sprite.h"
#include "globalVariables.h"
#include "BehaviourTrigger.h"
#include <string>

class BattlingCharacter;
class CardsInHand: public Entity
{
public:

	CardsInHand(){}

	CardsInHand(int x, ImageManager* imageManager) : cardsInHand(x),
		deckSprite(&PositionalEntity("DeckSprite",
			sf::Vector2f(setPosition(Alignment::right, Axis::x, -(windowInfo.UIWidth/2.0f)*windowInfo.tileSizeInPixels),
			setPosition(Alignment::centre, Axis::y, 0))
			,imageManager),
			imageManager,"card2")
	{
		selected = rand() % x;
		cardsInHand[selected].movementLocation = 1;
		cardsInHand[selected].offset = 1;
	}

	void initialise(BattlingCharacter* parent);

	void draw(sf::RenderWindow &window, const Entity* parent);

	void resize();

	int action(BattlingCharacter* parent);

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

