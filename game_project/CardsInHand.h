#include <vector>
#include <iostream>
#include <stdlib.h>
#include "Card.h"
#include "CardSprite.h"
#include "NumberEntity.h"
#include "WindowInfo.h"
#include "globalVariables.h"
static class CardsInHand: public Entity
{
public:
	CardsInHand(int x) : cardsInHand(x)
	{
		selected = rand() % x;
		cardsInHand[selected].position = 1;
		cardsInHand[selected].offset = 1;
	}

	void initialise(std::vector<Card>& cardsInDeck, std::vector<long double>& cardsRemaining, int windowedHeight,int windowedWidth, int fullscreen, int tileReductionX);

	void draw(sf::RenderWindow &window, std::vector<Card>& cardsInDeck);

	void action(std::map<int, bool> keyboardArray, std::vector<Card>& cardsInDeck,
				std::vector<long double>& cardsRemaining, WindowInfo windowInfo, int& cardIndex, float& cardPoints);

	void drawCard(std::vector<Card>& cardsInDeck, std::vector<long double>& cardsRemaining);

	void newMotion(int index);

	void cardInfoPrint(std::vector<Card>& cardsInDeck);

	void cardInfoDraw(std::vector<Card>& cardsInDeck, sf::RenderWindow& window);

	std::vector<CardSprite> cardsInHand;

private:

	std::map<AttackType,std::string> attackTypeMap = {{AttackType::circle, "Circle"}, { AttackType::line,"Line" },{AttackType::cross,"Cross"} };

	sf::Text text;
	sf::Font font;
	int pixelSize = 2;
	int tileSize = 16;
	Entity deckSprite;
	NumberEntity noOfCardsInHand;
	unsigned int selected;
	int drawCardCooldown = 10;
};

