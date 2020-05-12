#include "CardsInHand.h"
#include "SFML/Window.hpp"
#include <vector>
#include <assert.h>
#include <iomanip>
#include "easeInOut.h"
#include <string>
#include <sstream>


//print information about the card to console (its ID and name) DEBUG

void CardsInHand::newMotion(int index)
{
	cardsInHand[index].inMotion = true;
	cardsInHand[index].previousXPos = cardsInHand[index].xPos;
	cardsInHand[index].previousYPos = cardsInHand[index].yPos;
}

//print card info to console
void CardsInHand::cardInfoPrint(std::vector<Card>& cardsInDeck)
{
	std::cout << std::setprecision(40);
	std::cout << "ID of selected card: " << cardsInHand[selected].id << std::endl;
	std::cout << std::setprecision(3);
	for(int i=0;i<cardsInDeck.size();i++)
	{
		if (cardsInHand[selected].id == cardsInDeck[i].id)
		{
			std::cout << "Selected Cards Name: " << cardsInDeck[i].name<<std::endl
					<< "Attack Type: " << attackTypeMap[cardsInDeck[i].attackType] << " | Attack Radius: " <<
					cardsInDeck[i].attackRadius << " | Attack Speed:" << cardsInDeck[i].attackEmanationSpeed<<
					"| Persistence:"<<cardsInDeck[i].persistence<< std::endl;
			break;
		}
		
	}

}

void CardsInHand::cardInfoDraw(std::vector<Card>& cardsInDeck,sf::RenderWindow& window)
{
	
	for (int i = 0; i < cardsInDeck.size(); i++)
	{
		if (cardsInHand[selected].id == cardsInDeck[i].id)
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

void CardsInHand::initialise(std::vector<Card>& cardsInDeck, std::vector<long double>& cardsRemaining, int windowedHeight, int windowedWidth, int fullscreen,int tileReductionX)
{
	font.loadFromFile("assets/minecraft.ttf");
	text.setFont(font);
	text.setCharacterSize(16);
	if (fullscreen == 0)
	{
		deckSprite.initialise("card2.png", windowedWidth*pixelSize*tileSize - ((tileReductionX*pixelSize*tileSize) / 2), windowedHeight / 2 * pixelSize*tileSize, 1);
		text.setPosition(windowedWidth*pixelSize*tileSize - (tileReductionX - 1)*pixelSize*tileSize, (windowedHeight / 2 + 3) * pixelSize*tileSize);

	}
	else
	{
		deckSprite.initialise("card2.png", sf::VideoMode::getDesktopMode().width - ((tileReductionX*pixelSize*tileSize) / 2), sf::VideoMode::getDesktopMode().height/2.0, 1);
		text.setPosition(sf::VideoMode::getDesktopMode().width - (tileReductionX - 1)*pixelSize*tileSize, sf::VideoMode::getDesktopMode().height/2.0+3 * pixelSize*tileSize);
	}
	cardsInHand.clear();
	std::cout << cardsRemaining.size();
	noOfCardsInHand.initialise(deckSprite.xPos+(deckSprite.texture.getSize().x/2.0), deckSprite.yPos + (deckSprite.texture.getSize().y / 2.0), 0, cardsRemaining.size());
	drawCard(cardsInDeck,cardsRemaining);
	drawCard(cardsInDeck, cardsRemaining);
	drawCard(cardsInDeck, cardsRemaining);
	selected = 0;

}
void CardsInHand::draw(sf::RenderWindow &window, std::vector<Card>& cardsInDeck)
{

	deckSprite.draw(window);
	for (int i = 0; i < cardsInHand.size(); i++)
	{

		cardsInHand[i].draw(window);
		//std::cout << deckSprite.xPos << " " << deckSprite.yPos << std::endl;
		
	}
	cardInfoDraw(cardsInDeck,window);
	noOfCardsInHand.draw(window);
}

void CardsInHand::action(std::map<int, bool> keyboardArray, float frameTime, std::vector<Card>& cardsInDeck, std::vector<long double>& cardsRemaining,
						WindowInfo windowInfo, int& cardIndex,float& cardPoints)
{
	
	//move the deck sprite to its relative location if changing between fullscreen and windowed
	if (keyboardArray[sf::Keyboard::F11])
	{
		
		if (windowInfo.fullscreen == 1)
		{
		}
		else
		{
			
			deckSprite.xPos = windowInfo.windowedWidth * pixelSize*tileSize - ((windowInfo.tileReductionX*pixelSize*tileSize) / 2)-32;
			deckSprite.yPos = (windowInfo.windowedHeight * pixelSize*tileSize) / 2.0-48 ;

			//std::cout << deckSprite.xPos << " " << deckSprite.yPos << std::endl;

			for (int i = 0; i < cardsInHand.size(); i++)
			{
				cardsInHand[i].previousYPos = cardsInHand[i].previousYPos - (sf::VideoMode::getDesktopMode().height - windowInfo.windowedHeight * 32);
				cardsInHand[i].yPos = cardsInHand[i].yPos - (sf::VideoMode::getDesktopMode().height - windowInfo.windowedHeight*32);
			}
			
		}
	}

	//MOTION

		drawCardCooldown++;

		//DRAW NEW CARD

		if (keyboardArray[sf::Keyboard::LControl] && drawCardCooldown>=15)
		{
			drawCardCooldown = 0;
			drawCard(cardsInDeck,cardsRemaining);
		}
		
		bool inMotion=false;
		for (int i=0;i<cardsInHand.size();i++)
		{
			if (cardsInHand[i].inMotion == true)
			{
				inMotion = true;
				break;
		}
		}

		

		//only initiate new  motion if no card is currently in motion

		if (inMotion==false)
		{
			//SELECTION 

			//only allows selection moving if we have more than 1 card
			if ((keyboardArray[sf::Keyboard::Left] || keyboardArray[sf::Keyboard::Right]) && cardsInHand.size() > 1)
			{
				newMotion(selected);
				if (keyboardArray[sf::Keyboard::Left])
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
				cardInfoPrint(cardsInDeck);
				newMotion(selected);
			}	

			//USE CARD

			//TODO ensure this can only happen when the player is stationary

			else if (keyboardArray[sf::Keyboard::Enter])
			{
				
				long double cardSelected = cardsInHand[selected].id;

				//Firstly, find and save the index of the selected card in the deck

				for (int i = 0; i <cardsInDeck.size(); i++)
				{
					if (cardSelected == cardsInDeck[i].id)
					{
						cardIndex = i;
						break;
					}
				}

				assert(cardIndex != 10000);

				if (cardPoints >= cardsInDeck[cardIndex].cardPointCost)
				{
					cardPoints -= cardsInDeck[cardIndex].cardPointCost;
				}
				else { cardIndex = 10000; return; }

				for (int i = selected+2; i < cardsInHand.size(); i++)
				{
					cardsInHand[i].position = 3;
					newMotion(i);
				}

				//selected the next card unless the last card is already selected in which case it selects the previous card
				if (selected == cardsInHand.size() - 1)
				{
					newMotion(selected-1);
					cardsInHand.erase(cardsInHand.begin() + selected);
					selected--;
				}
				else
				{
					cardsInHand[selected + 1].position = 4;
					newMotion(selected + 1);
					cardsInHand.erase(cardsInHand.begin() + selected);
				}
				
				newMotion(selected);
			}
	}

	//move all the cards currently in motion
	for (int i = 0; i < cardsInHand.size(); i++)
	{
		if (cardsInHand[i].inMotion==true)
		{
			cardsInHand[i].move(frameTime, i, windowInfo);
		}

		
	}



}

void CardsInHand::drawCard(std::vector<Card>& cardsInDeck, std::vector<long double>& cardsRemaining)
{
	if (cardsRemaining.size()>0)
	{
		std::cout << "Drawing New Card" << std::endl;

		CardSprite newCard;


		//choose a new card from the list of remaining cards

		int rando = rand();
		//std::cout << cardsRemaining.size() << " " << rando << std::endl;
		int index = rando % cardsRemaining.size();
		newCard.id = cardsRemaining[index];
		cardsRemaining.erase(cardsRemaining.begin() + index);
		noOfCardsInHand.value--;
		newCard.initialise(deckSprite);
		cardsInHand.push_back(newCard);

		//for some reason this breaks the textures so we now have to reload them
		for (int i = 0; i < cardsInHand.size(); i++)
		{
			texture.loadFromFile("assets/card2.png");
			cardsInHand[i].sprite.setTexture(texture);
		}
	}
	else
	{
		std::cout << "There are no cards in the deck!" << std::endl;
	}
}