#include "CardActionMap.h"
#include <assert.h>


CardActionMap::CardActionMap()
{
}

void CardActionMap::reset() {
	//TODO
}

void CardActionMap::newAction(Card& card, int direction, sf::Vector2i playerPos, std::vector<std::vector<int>>& collision)
{
	std::vector<std::vector<int>> directionMap = { {0,-1},{-1,0},{0,1},{1,0} };

	switch (card.attackType)
	{
	case(AttackType::line):
	
		for (int i = 0; i < card.attackRadius; i++)
		{
			unsigned int xPos;
			unsigned int yPos;

			xPos = playerPos.x+directionMap[direction][0]*(i+1);
			yPos = playerPos.y+directionMap[direction][1]*(i+1);

			pushBackActionMap(sf::Vector2i(xPos,yPos), playerPos, collision, i, card);
		}
		
	case(AttackType::cross):
	
		unsigned int xPos;
		unsigned int yPos;

		for (int i = 0; i < card.attackRadius; i++)
		{

			for (int j = 0; j < 4; j++)
			{

				xPos = playerPos.x + (i + 1) * directionMap[j][0];
				yPos = playerPos.y + (i + 1) * directionMap[j][1];

				pushBackActionMap(sf::Vector2i(xPos, yPos), playerPos, collision, i, card);
			}

		}
		break;
	
	case(AttackType::circle):
	
		int tileRadius = card.attackRadius;

		for (int i = playerPos.x - tileRadius; i < playerPos.x + tileRadius + 1; i++)
		{
			for (int j = playerPos.y - tileRadius; j < playerPos.y + tileRadius + 1; j++)
			{

				float euclideanDistance = sqrtf(powf(static_cast<float>(playerPos.x - i), 2) + powf(static_cast<float>(playerPos.y - j), 2));

				if (euclideanDistance <= tileRadius)
				{
					pushBackActionMap(sf::Vector2i(i, j), playerPos, collision, euclideanDistance, card);
				}

			}
		}
		break;
	}
}


/**
* Ensures the proposed card action point is within range of the map and within line
* of sight of the player. If so it pushes back an action point at the location specified
* @param pos The position of the proposed action point
* @param playerPos location of the player
* @param collision The collision map for line of sight calculation
* @param pointDistance The distance of the proposed point
* @param card The card whose parameters are passed to the card action point
*/
void CardActionMap::pushBackActionMap(sf::Vector2i pos,sf::Vector2i playerPos,std::vector<std::vector<int>> collision,
									  float pointDistance, Card card)
{
	//check if it goes out of range of the map
	if (pos.x < 0 || pos.x >= static_cast<signed int>(collision[0].size()) || pos.y < 0 || pos.y >= static_cast<signed int>(collision.size()))
	{
		return;
	}

	//check whether there is line of sight
	if (lineOfSightObstructed(playerPos.x, playerPos.y, pos.x, pos.y, collision)) { return; }

	float activationTime = pointDistance * (0.1f / card.attackEmanationSpeed);

	CardAction newCardAction(pos.x, pos.y, activationTime,
							activationTime + card.persistence,
							card.attackElement, card.attackDamage);

	cardActionMap.push_back(newCardAction);
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
	std::vector<sf::Vector2i> v;
	v = standaloneFunctions::lineOfSight(xPos1, yPos1, xPos2, yPos2);

	for (unsigned int k = 0; k < v.size(); k++)
	{
		if (collision[v[k].y][v[k].x] == 1)
		{
			return true;
		}
	}

	return false;
}