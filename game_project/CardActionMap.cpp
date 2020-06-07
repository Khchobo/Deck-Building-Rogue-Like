#include "CardActionMap.h"
#include <assert.h>


CardActionMap::CardActionMap()
{
}

void CardActionMap::reset() {
	//TODO
}

void CardActionMap::newAction(int cardIndex, CardsInDeck cardsInDeck, int direction, sf::Vector2i playerPos, std::vector<std::vector<int>> collision)
{
	std::vector<std::vector<int>> directionMap = { {0,-1},{-1,0},{0,1},{1,0} };

	switch (cardsInDeck.cardsInDeck[cardIndex].attackType)
	{
	case(AttackType::line):
	{
		for (int i = 0; i < cardsInDeck.cardsInDeck[cardIndex].attackRadius; i++)
		{
			int xPos;
			int yPos;

			xPos = playerPos.x+directionMap[direction][0]*(i+1);
			yPos = playerPos.y+directionMap[direction][1]*(i+1);

			//check if it goes out of range of the map
			if (xPos < 0 || xPos >= collision[0].size() || yPos < 0 || yPos >= collision.size())
			{
				continue;
			}

			if (lineOfSightObstructed(playerPos.x, playerPos.y, xPos, yPos, collision)) { continue; }

			float activationTime = i * (0.1 / cardsInDeck.cardsInDeck[cardIndex].attackEmanationSpeed);

			CardAction newCardAction(xPos, yPos, activationTime, activationTime + cardsInDeck.cardsInDeck[cardIndex].persistence,
				cardsInDeck.cardsInDeck[cardIndex].attackElement);
			cardActionMap.push_back(newCardAction);

		line_finish:;
		}
		break;
	}
	case(AttackType::cross):
	{
		float activationTime;
		int xPos;
		int yPos;

		for (int i = 0; i < cardsInDeck.cardsInDeck[cardIndex].attackRadius; i++)
		{

			activationTime = i * (0.1 / cardsInDeck.cardsInDeck[cardIndex].attackEmanationSpeed);
			for (int j = 0; j < 4; j++)
			{

				xPos = playerPos.x + (i + 1) * directionMap[j][0];
				yPos = playerPos.y + (i + 1) * directionMap[j][1];

				//check if it goes out of range of the map
				if (xPos < 0 || xPos >= collision[0].size() || yPos < 0 || yPos >= collision.size())
				{
					continue;
				}

				if (lineOfSightObstructed(playerPos.x, playerPos.y, xPos, yPos, collision)) {
					continue;
				}

				CardAction newCardAction(xPos, yPos, activationTime, activationTime + cardsInDeck.cardsInDeck[cardIndex].persistence,
					cardsInDeck.cardsInDeck[cardIndex].attackElement);
				cardActionMap.push_back(newCardAction);
			}

		}
		break;
	}
	case(AttackType::circle):
	{
		int tileRadius = cardsInDeck.cardsInDeck[cardIndex].attackRadius;

		float activationTime;

		for (int i = playerPos.x - tileRadius; i < playerPos.x + tileRadius + 1; i++)
		{
			for (int j = playerPos.y - tileRadius; j < playerPos.y + tileRadius + 1; j++)
			{
				//check if it goes out of range of the map
				if (i < 0 || i >= collision[0].size() || j < 0 || j >= collision.size())
				{
					continue;
				}

				float euclideanDistance = sqrt(pow((playerPos.x - i), 2) + pow((playerPos.y - j), 2));

				if (euclideanDistance <= tileRadius)
				{
					if (lineOfSightObstructed(playerPos.x, playerPos.y, i, j, collision)) { continue; }

					activationTime= euclideanDistance * (0.1 / cardsInDeck.cardsInDeck[cardIndex].attackEmanationSpeed);

					CardAction newCardAction(i, j, activationTime, activationTime + cardsInDeck.cardsInDeck[cardIndex].persistence,
												cardsInDeck.cardsInDeck[cardIndex].attackElement);
					cardActionMap.push_back(newCardAction);
				}

			}

		}

		break;
	}





	}
}

void CardActionMap::updateAllCardActions(float frameTime)
{

	auto i = cardActionMap.begin();
	while (i !=cardActionMap.end())
	{

		int index= std::distance(cardActionMap.begin(), i);

		cardActionMap[index].aliveTime += frameTime;

		if (cardActionMap[index].aliveTime>= cardActionMap[index].activationTime && !(cardActionMap[index].aliveTime >= cardActionMap[index].destructionTime))
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

/**
* Checks whether there is line of sight between two points. Returns false if there is line of sight and returns
* true if line of sight is obstructed.
* @param xPos1 the x position of the first point
* @param yPos1 the y position of the first point
* @param xPos2 the x position of the second point
* @param yPos2 the y position of the second point
* @param collision the map of cells indicating whether there is a solid object at a given point
*/
bool CardActionMap::lineOfSightObstructed(int xPos1,int yPos1,int xPos2,int yPos2, std::vector<std::vector<int>> collision)
{
	std::vector<Point> v;
	v = standaloneFunctions::lineOfSight(xPos1, yPos1, xPos2, yPos2);

	for (int k = 0; k < v.size(); k++)
	{
		if (collision[v[k].y][v[k].x] == 1)
		{
			return true;
		}
	}

	return false;
}