#include "CardActionMap.h"
#include <assert.h>


CardActionMap::CardActionMap()
{
}

void CardActionMap::reset() {
	//TODO
}

void CardActionMap::newAction(int cardIndex, CardsInDeck cardsInDeck, int direction, int playerXPos, int playerYPos, std::vector<std::vector<int>> collision)
{

	switch (cardsInDeck.cardsInDeck[cardIndex].attackType)
	{
	case(AttackType::line):
		for (int i = 0; i < cardsInDeck.cardsInDeck[cardIndex].attackRadius;i++)
		{
			int xPos;
			int yPos;
			switch (direction)
			{
			case(0):
				xPos = playerXPos;
				yPos = playerYPos - 1 - i;
				break;
			case(1):
				xPos = playerXPos - 1 - i;
				yPos = playerYPos;
				break;
			case(2):
				xPos = playerXPos;
				yPos = playerYPos + 1 + i;
				break;
			case(3):
				xPos = playerXPos + 1 + i;
				yPos = playerYPos;
				break;
			}

			if (xPos < 0 || xPos >= collision[0].size() || yPos < 0 || yPos >= collision.size())
			{
				continue;
			}

			std::vector<Point> v = lineOfSight(playerXPos, playerYPos, xPos, yPos);

			ActionPoint newActionPoint(xPos, yPos, i*(0.1 / cardsInDeck.cardsInDeck[cardIndex].attackEmanationSpeed), i*(0.1 / cardsInDeck.cardsInDeck[cardIndex].attackEmanationSpeed) + 0.5, cardsInDeck.cardsInDeck[cardIndex].attackElement);
			for (int k = 0; k < v.size(); k++)
			{
				if (collision[v[k].y][v[k].x] == 1)
				{
					goto line_finish;
				}
			}

			cardActionMap.push_back(newActionPoint);

		line_finish:;
		}
		break;
	case(AttackType::cross):
		for (int i = 0; i < cardsInDeck.cardsInDeck[cardIndex].attackRadius; i++)
		{
			//TODO clean up this horrible mess
			ActionPoint newActionPoint(playerXPos+i+1, playerYPos, i*(0.1 / cardsInDeck.cardsInDeck[cardIndex].attackEmanationSpeed), i*(0.1 / cardsInDeck.cardsInDeck[cardIndex].attackEmanationSpeed) + 0.5, cardsInDeck.cardsInDeck[cardIndex].attackElement);
			cardActionMap.push_back(newActionPoint);
			ActionPoint newActionPoint2(playerXPos - i-1, playerYPos, i*(0.1 / cardsInDeck.cardsInDeck[cardIndex].attackEmanationSpeed), i*(0.1 / cardsInDeck.cardsInDeck[cardIndex].attackEmanationSpeed) + 0.5, cardsInDeck.cardsInDeck[cardIndex].attackElement);
			cardActionMap.push_back(newActionPoint2);
			ActionPoint newActionPoint3(playerXPos, playerYPos+i+1, i*(0.1 / cardsInDeck.cardsInDeck[cardIndex].attackEmanationSpeed), i*(0.1 / cardsInDeck.cardsInDeck[cardIndex].attackEmanationSpeed) + 0.5, cardsInDeck.cardsInDeck[cardIndex].attackElement);
			cardActionMap.push_back(newActionPoint3);
			ActionPoint newActionPoint4(playerXPos, playerYPos-i-1, i*(0.1 / cardsInDeck.cardsInDeck[cardIndex].attackEmanationSpeed), i*(0.1 / cardsInDeck.cardsInDeck[cardIndex].attackEmanationSpeed) + 0.5, cardsInDeck.cardsInDeck[cardIndex].attackElement);
			cardActionMap.push_back(newActionPoint4);
			
		}
		break;
	case(AttackType::circle):
		
		int tileRadius = cardsInDeck.cardsInDeck[cardIndex].attackRadius;

		std::cout << playerXPos << " " << playerYPos << std::endl << std::endl;

		for (int i = playerXPos - tileRadius; i < playerXPos + tileRadius+1; i++)
		{
			for (int j = playerYPos - tileRadius; j < playerYPos + tileRadius+1; j++)
			{
				
				float euclideanDistance = sqrt(pow((playerXPos - i),2) + pow((playerYPos - j), 2));
				//std::cout << i << " " << j << " " << euclideanDistance << std::endl;

				if (i<0 || i>=collision[0].size() || j<0 || j>=collision.size())
				{
					goto circle_finish;
				}

				if (euclideanDistance<=tileRadius)
				{
					std::vector<Point> v = lineOfSight(playerXPos, playerYPos, i, j);

					for (int k = 0; k < v.size(); k++)
					{
						if (collision[v[k].y][v[k].x] == 1)
						{
							goto circle_finish;
						}
					}

					ActionPoint newActionPoint(i, j, euclideanDistance*(0.1 / cardsInDeck.cardsInDeck[cardIndex].attackEmanationSpeed),
						euclideanDistance*(0.1 / cardsInDeck.cardsInDeck[cardIndex].attackEmanationSpeed) + cardsInDeck.cardsInDeck[cardIndex].persistence, cardsInDeck.cardsInDeck[cardIndex].attackElement);
					cardActionMap.push_back(newActionPoint);
				}
			circle_finish:;
			}
			
		}

		break;
	}


	
	


}

void CardActionMap::action(float frameTime)
{
	auto i = cardActionMap.begin();
	while (i !=cardActionMap.end())
	{

		int index= std::distance(cardActionMap.begin(), i);

		cardActionMap[index].aliveTime += frameTime;
		//std::cout << index << " " << cardActionMap[index].aliveTime<<" "<< cardActionMap[index].activationTime << std::endl;

		if (cardActionMap[index].aliveTime>= cardActionMap[index].activationTime)
		{
			cardActionMap[index].active = true;
		}
		if (cardActionMap[index].aliveTime >= cardActionMap[index].destructionTime)
		{
			i=cardActionMap.erase(cardActionMap.begin()+index);
			continue;
		}
		i++;
	}
}