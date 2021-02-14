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

	CardsInHand(int x, ImageManager* imageManager, BattlingCharacter* parentObject) : cardsInHand(x),
		deckSprite("DeckSprite",
			sf::Vector2f(setPosition(Alignment::right, Axis::x, -(windowInfo.UIWidth/2.0f)*windowInfo.tileSizeInPixels),
			setPosition(Alignment::centre, Axis::y, 0))
			,imageManager, "card2", (PositionalEntity*)(parentObject), (PositionalEntity*)(parentObject))
	{}

	void initialise(BattlingCharacter* parent);
	void draw(sf::RenderWindow &window, const Entity* parent);
	void resize();
	int  action(BattlingCharacter* parent);
	void cardInfoPrint(std::vector<Card>& cardsInDeck);
	void cardInfoDraw(const std::vector<Card>& cardsInDeck, sf::RenderWindow& window);
	void changeSelection(unsigned int& selected, std::string identifier, std::vector<std::unique_ptr<CardSprite>>& cardsInHand,
							std::map<BehaviourTrigger, bool> behaviourTriggers, std::vector<Card>& cardsInDeck);
	unsigned int GetSelectedCard();
	bool anyCardsInMotion(std::vector<std::unique_ptr<CardSprite>>& cardsInHand);
	void drawCard(BattlingCharacter* parent);

	std::vector<std::unique_ptr<CardSprite>> cardsInHand;

private:

	std::map<AttackType,std::string> attackTypeMap = {{AttackType::circle, "Circle"}, { AttackType::line,"Line" },{AttackType::cross,"Cross"} };

	sf::Text text;
	sf::Font font;

	PositionalEntity deckSprite;
	NumberEntity noOfCardsInHand;
	unsigned int selected;
	int drawCardCooldown = 10;
};

