#pragma once
#include <vector>
#include <iostream>
#include <iomanip>
#include "Card.h"

class CardsInDeck
{
public:
	
	CardsInDeck() {};

	CardsInDeck(BattlingCharacterType* type): cardsRemaining(type->deckSize)
	{

		std::cout << std::setprecision(60);
		for (unsigned int i = 0; i < type->deckSize; i++)
		{

			cardsInDeck.push_back(Card(type));

			//add the ID to cards remaining
			cardsRemaining[i] = cardsInDeck[i].id;
			std::cout << "Card "<<i<<" ID="<< cardsInDeck[i].id<<std::endl;
		}
		std::cout << std::setprecision(3);
	};

	void initialiseRandomDeck();

	void resetDeck();

	std::vector<Card> cardsInDeck;

	//track the cards in the deck but not in the hand (to draw from)
	std::vector<long double> cardsRemaining;
};