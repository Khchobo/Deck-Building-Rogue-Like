#include "CardsInDeck.h"

void CardsInDeck::resetDeck()
{
	cardsRemaining.clear();
	for (unsigned int i = 0; i < cardsInDeck.size(); i++)
	{
		//add the ID to cards remaining
		cardsRemaining.push_back(cardsInDeck[i].id);
	}
}