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
	{
		for (int i = 0; i < cardsInDeck.cardsInDeck[cardIndex].attackRadius; i++)
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
			default:
				assert(false);
				break;
			}

			if (xPos < 0 || xPos >= collision[0].size() || yPos < 0 || yPos >= collision.size())
			{
				continue;
			}

			float activationTime = i * (0.1 / cardsInDeck.cardsInDeck[cardIndex].attackEmanationSpeed);

			if (lineOfSightObstructed(playerXPos, playerYPos, xPos, yPos, collision)) { continue; }

			ActionPoint newActionPoint(xPos, yPos, activationTime, activationTime + cardsInDeck.cardsInDeck[cardIndex].persistence,
				cardsInDeck.cardsInDeck[cardIndex].attackElement);
			cardActionMap.push_back(newActionPoint);

		line_finish:;
		}
		break;
	}
	case(AttackType::cross):
	{
		std::vector<std::vector<int>> directionMap = { {1,0},{-1,0},{0,1},{0,-1} };
		float activationTime;
		int xPos;
		int yPos;

		for (int i = 0; i < cardsInDeck.cardsInDeck[cardIndex].attackRadius; i++)
		{

			activationTime = i * (0.1 / cardsInDeck.cardsInDeck[cardIndex].attackEmanationSpeed);
			for (int j = 0; j < 4; j++)
			{

				xPos = playerXPos + i * directionMap[j][0] + directionMap[j][0];
				yPos = playerYPos + i * directionMap[j][1] + directionMap[j][1];

				if (xPos < 0 || xPos >= collision[0].size() || yPos < 0 || yPos >= collision.size())
				{
					continue;
				}

				if (lineOfSightObstructed(playerXPos, playerYPos, xPos, yPos, collision)) {
					continue;
				}

				ActionPoint newActionPoint(xPos, yPos, activationTime, activationTime + cardsInDeck.cardsInDeck[cardIndex].persistence,
					cardsInDeck.cardsInDeck[cardIndex].attackElement);
				cardActionMap.push_back(newActionPoint);
			}

		}
		break;
	}
	case(AttackType::circle):
	{
		int tileRadius = cardsInDeck.cardsInDeck[cardIndex].attackRadius;

		float activationTime;

		for (int i = playerXPos - tileRadius; i < playerXPos + tileRadius + 1; i++)
		{
			for (int j = playerYPos - tileRadius; j < playerYPos + tileRadius + 1; j++)
			{

				float euclideanDistance = sqrt(pow((playerXPos - i), 2) + pow((playerYPos - j), 2));
				//std::cout << i << " " << j << " " << euclideanDistance << std::endl;

				if (i < 0 || i >= collision[0].size() || j < 0 || j >= collision.size())
				{
					continue;
				}

				if (euclideanDistance <= tileRadius)
				{
					if (lineOfSightObstructed(playerXPos, playerYPos, i, j, collision)) { continue; }

					activationTime= euclideanDistance * (0.1 / cardsInDeck.cardsInDeck[cardIndex].attackEmanationSpeed);

					ActionPoint newActionPoint(i, j, activationTime, activationTime + cardsInDeck.cardsInDeck[cardIndex].persistence,
												cardsInDeck.cardsInDeck[cardIndex].attackElement);
					cardActionMap.push_back(newActionPoint);
				}

			}

		}

		break;
	}





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