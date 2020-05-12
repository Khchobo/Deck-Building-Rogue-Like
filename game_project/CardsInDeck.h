#include <vector>
#include <iostream>
#include <iomanip>
#include "Card.h"

#ifndef CARDSINDECK_HEADER
#define CARDSINDECK_HEADER

class CardsInDeck
{
public:
	
	CardsInDeck();

	CardsInDeck(int n): cardsInDeck(n), cardsRemaining(n)
	{
		std::cout << std::setprecision(60);
		for (int i=0;i<cardsInDeck.size();i++)
		{
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

#endif