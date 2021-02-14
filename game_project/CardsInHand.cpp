#include "CardsInHand.h"
#include "SFML/Window.hpp"
#include "entities\characters\BattlingCharacter.h"
#include <vector>
#include <assert.h>
#include <iomanip>
#include <string>
#include <sstream>

using namespace standaloneFunctions;

#define ALIGN Alignment

void CardsInHand::initialise(BattlingCharacter* parent)
{
	cardsInHand.clear();
	if (parent->identity == "player")
	{

		font.loadFromFile("assets/minecraft.ttf");
		text.setFont(font);
		text.setCharacterSize(16);

		//one tile to the right from the edge of the UI box
		float initialX = setPosition(ALIGN::right, Axis::x, -(windowInfo.UIWidth - 1.0f)*windowInfo.tileSizeInPixels);
		//3 tiles lower than centre
		float initialY = setPosition(ALIGN::centre, Axis::y, 3.0f * windowInfo.tileSizeInPixels);

		text.setPosition(initialX, initialY);

		noOfCardsInHand.initialise(sf::Vector2f(deckSprite.position.x - 6, deckSprite.position.y - 9), parent->cardsInDeck.cardsRemaining.size());
	}

	for (int i = 0; i < parent->type->maxHandSize; i++)
	{
		drawCard(parent);
	}
	selected = 0;
}

//print card info to console
void CardsInHand::cardInfoPrint(std::vector<Card>& cardsInDeck)
{
	std::cout << std::setprecision(40);
	std::cout << "ID of selected card: " << cardsInHand[selected]->id << std::endl;
	std::cout << std::setprecision(3);
	for(unsigned int i=0;i<cardsInDeck.size();i++)
	{
		if (cardsInHand[selected]->id == cardsInDeck[i].id)
		{
			std::cout << "Selected Cards Name: " << cardsInDeck[i].name<<std::endl
					<< "Attack Type: " << attackTypeMap[cardsInDeck[i].attackType] << " | Attack Radius: " <<
					cardsInDeck[i].attackRadius << " | Attack Speed:" << cardsInDeck[i].attackEmanationSpeed<<
					"| Persistence:"<<cardsInDeck[i].persistence<< std::endl;
			break;
		}
		
	}

}

void CardsInHand::cardInfoDraw(const std::vector<Card>& cardsInDeck,sf::RenderWindow& window)
{
	
	for (unsigned int i = 0; i < cardsInDeck.size(); i++)
	{
		if (cardsInHand[selected]->id == cardsInDeck[i].id)
		{
			std::ostringstream streamObj3;
			streamObj3 << std::setprecision(2);
			streamObj3 << cardsInDeck[i].name << "\nAttack Type: " << attackTypeMap[cardsInDeck[i].attackType] << "\nAttack Radius: "
				<< cardsInDeck[i].attackRadius << "\nAttack Speed: " << cardsInDeck[i].attackEmanationSpeed <<
				"\nCost: " << cardsInDeck[i].cardPointCost;

			text.setString(streamObj3.str());
			break;
		}

	}
	
	window.draw(text);
}

void CardsInHand::draw(sf::RenderWindow &window, const Entity* parent)
{
	GET_OBJECT_COMPONENT(Sprite, "Sprite", deckSprite)->draw(window, Sprite::CoordSpace::viewportSpace);
	for (unsigned int i = 0; i < cardsInHand.size(); i++)
	{
 		GET_OBJECT_POINTER_COMPONENT(Sprite, "Sprite", cardsInHand[i])->draw(window, Sprite::CoordSpace::viewportSpace);	
	}
	cardInfoDraw((dynamic_cast<const BattlingCharacter*>(parent))->cardsInDeck.cardsInDeck,window);
	noOfCardsInHand.draw(window);
}

//move the deck sprite to its relative location if changing between fullscreen and windowed
void CardsInHand::resize()
{

	float tempX = setPosition(ALIGN::right, Axis::x, -(windowInfo.UIWidth - 1.0f)*windowInfo.tileSizeInPixels);
	float tempY = setPosition(ALIGN::centre, Axis::y, 3.0f * windowInfo.tileSizeInPixels);

	text.setPosition(tempX, tempY);

	deckSprite.position.x = setPosition(ALIGN::right, Axis::x, -((windowInfo.UIWidth*windowInfo.tileSizeInPixels) / 2.0f + 32.0f));

	//centred as it is moved up by 48 i.e. half the length of the card
	deckSprite.position.y = setPosition(ALIGN::centre, Axis::y, -48);

	//*noOfCardsInHand.position = deckSprite.position; //TODO MAKE NUMBER ENTITY A POSITIONAL ENTITY

	for (unsigned int i = 0; i < cardsInHand.size(); i++)
	{
		cardsInHand[i]->previousPos.y = cardsInHand[i]->previousPos.y + (windowInfo.getWindowHeight() - windowInfo.windowedHeightPixels);
		cardsInHand[i]->position.y = cardsInHand[i]->position.y + (windowInfo.getWindowHeight() - windowInfo.windowedHeightPixels);
	}
}

int CardsInHand::action(BattlingCharacter* parent)
{

	//MOTION

		drawCardCooldown++;

		//DRAW NEW CARD

		if (parent->behaviourTriggers[drawCardFromDeck] && drawCardCooldown>=15)
		{
			drawCardCooldown = 0;
			drawCard(parent);
		}
		
		bool inMotion=false;

		if (parent->identity == "player")
		{
			inMotion = anyCardsInMotion(cardsInHand);
		}

		//only initiate new  motion if no card is currently in motion

		if (inMotion==false)
		{
			//SELECTION 

			//only allows selection moving if we have more than 1 card
			if ((parent->behaviourTriggers[selectCardLeft] || parent->behaviourTriggers[selectCardRight]) && cardsInHand.size() > 1)
			{
				changeSelection(selected, parent->identity, cardsInHand, parent->behaviourTriggers, parent->cardsInDeck.cardsInDeck);
			}	

			//USE CARD

			//TODO ensure this can only happen when the player is stationary

			else if (parent->behaviourTriggers[useCard] && cardsInHand.size() > 1)
			{
				int deckCardIndex;
				long double cardSelected = cardsInHand[selected]->id;

				//Firstly, find and save the index of the selected card in the deck

				for (unsigned int i = 0; i < parent->cardsInDeck.cardsInDeck.size(); i++)
				{
					if (cardSelected == parent->cardsInDeck.cardsInDeck[i].id)
					{
						deckCardIndex = i;
						break;
					}
				}

				if (parent->cardPoints >= parent->cardsInDeck.cardsInDeck[deckCardIndex].cardPointCost)
				{
					parent->cardPoints -= parent->cardsInDeck.cardsInDeck[deckCardIndex].cardPointCost;
				}
				else { return 0; }

				parent->behaviourTriggers[useCardSuccess] = true;

				for (unsigned int i = selected+2; i < cardsInHand.size(); i++)
				{
					cardsInHand[i]->SetState(CardSprite::CardLocationState::BelowUsedNotBecomingSelected);
				}

				//selected the next card unless the last card is already selected in which case it selects the previous card
				if (selected == cardsInHand.size() - 1)
				{
					cardsInHand[selected - 1]->SetState(CardSprite::CardLocationState::BecomingSelected);
					cardsInHand.erase(cardsInHand.begin() + selected);
					selected--;
				}
				else
				{
					cardsInHand[selected + 1]->SetState(CardSprite::CardLocationState::BelowUsedBecomingSelected);
					cardsInHand.erase(cardsInHand.begin() + selected);
				}
				
				return deckCardIndex;
			}
	}

	//move all the cards currently in motion
	for (unsigned int i = 0; i < cardsInHand.size(); i++)
	{
		if (cardsInHand[i]->inMotion==true)
		{
			cardsInHand[i]->UpdateCardMotion(i);
		}
	}

	return 0;
}

void CardsInHand::changeSelection(unsigned int& selected, std::string identifier, std::vector<std::unique_ptr<CardSprite>>& cardsInHand,
									std::map<BehaviourTrigger, bool> behaviourTriggers, std::vector<Card>& cardsInDeck)
{
	if (identifier == "player")
	{
		cardsInHand[selected]->SetState(CardSprite::CardLocationState::BecomingUnselected);
	}
	if (behaviourTriggers[selectCardLeft])
	{
		if (selected == 0)
		{
			selected = cardsInHand.size() - 1;
		}
		else {
			selected = (selected - 1) % cardsInHand.size();
		}
	}
	else
	{
		selected = (selected + 1) % cardsInHand.size();
	}
	if (identifier == "player")
	{
		cardsInHand[selected]->SetState(CardSprite::CardLocationState::BecomingSelected);
	}
}

unsigned int CardsInHand::GetSelectedCard()
{
	return selected;
}

bool CardsInHand::anyCardsInMotion(std::vector<std::unique_ptr<CardSprite>>& cardsInHand)
{
	for (unsigned int i = 0; i < cardsInHand.size(); i++)
	{
		if (cardsInHand[i]->inMotion == true)
		{
			return true;
		}
	}
	return false;
}

void CardsInHand::drawCard(BattlingCharacter* parent)
{
	if (parent->cardsInDeck.cardsRemaining.size()>0)
	{
		if (parent->identity == "player")
		{
			cardsInHand.push_back(std::make_unique<CardSprite>(&static_cast<PositionalEntity>(deckSprite), parent->imageManager, this));

			std::cout << "Drawing New Card" << std::endl;
			//choose a new card from the list of remaining cards

			int rando = rand();
			int index = rando % parent->cardsInDeck.cardsRemaining.size();
			cardsInHand[cardsInHand.size()-1]->id = parent->cardsInDeck.cardsRemaining[index];
			parent->cardsInDeck.cardsRemaining.erase(parent->cardsInDeck.cardsRemaining.begin() + index);
			noOfCardsInHand.value--;
		}
	}
	else
	{
		std::cout << "There are no cards in the deck!" << std::endl;
	}
}