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

	CardsInHand(int x, ImageManager* imageManager, Entity* parentObject, Entity* rootObject) : Entity("CardsInHand", parentObject, rootObject),  cardsInHand(x),
		deckSprite("DeckSprite",
			sf::Vector2f(setPosition(Alignment::right, Axis::x, -(windowInfo.UIWidth/2.0f)*windowInfo.tileSizeInPixels),
			setPosition(Alignment::centre, Axis::y, 0))
			,imageManager, "card2", this, rootObject)
	{}

	void Initialise() override;
	void Update() override;

	void draw(sf::RenderWindow &window, const Entity* parent);
	void resize();
	
	void cardInfoPrint(std::vector<Card>& cardsInDeck);
	void cardInfoDraw(const std::vector<Card>& cardsInDeck, sf::RenderWindow& window);
	void changeSelection(unsigned int& selected, std::string identifier, std::vector<std::unique_ptr<CardSprite>>& cardsInHand,
							std::map<BehaviourTrigger, bool> behaviourTriggers, std::vector<Card>& cardsInDeck);
	unsigned int GetSelectedCard();
	bool anyCardsInMotion(std::vector<std::unique_ptr<CardSprite>>& cardsInHand);
	void DrawCard();

	std::vector<std::unique_ptr<CardSprite>> cardsInHand;

private:

	std::map<AttackType,std::string> attackTypeMap = {{AttackType::circle, "Circle"}, { AttackType::line,"Line" },{AttackType::cross,"Cross"} };

	sf::Text text;
	sf::Font font;

	PositionalEntity deckSprite;
	//NumberEntity noOfCardsInHand;
	unsigned int selected;
	int drawCardCooldown = 10;
};

