#include "TileMap.h"

void TileMap::initialise()
{
		spriteImages[0].loadFromFile("assets/air_0.png");
		spriteImages[1].loadFromFile("assets/flowers_0.png");
		spriteImages[2].loadFromFile("assets/flowers_1.png");
		spriteImages[3].loadFromFile("assets/rock_0.png");
		spriteImages[4].loadFromFile("assets/rock_1.png");
		spriteImages[5].loadFromFile("assets/rock_2.png");
		spriteImages[6].loadFromFile("assets/rock_3.png");
		spriteImages[7].loadFromFile("assets/rock_4.png");
		spriteImages[8].loadFromFile("assets/cardAction.png");
		spriteImages[9].loadFromFile("assets/crystal.png");
}

void TileMap::draw(sf::Texture& texture) const
{
	for (unsigned int xPos = 0; xPos < mapWidth; xPos++)
	{
		for (unsigned int yPos = 0; yPos < mapHeight; yPos++)
		{
			//std::cout << mapTileType[yPos*mapWidth + xPos];
			texture.update(spriteImages[mapTilesWCardActions[yPos*mapWidth + xPos]], xPos*tileSize*pixelSize, yPos*tileSize*pixelSize);
		}
	}
}

void TileMap::initiateMap()
{
	int temp;
	srand(layoutSeed);
	for (unsigned int xPos = 0; xPos < mapWidth; xPos++)
	{
		for (unsigned int yPos = 0; yPos < mapHeight; yPos++)
		{

			//set flowers mode
			if (setFlowers)
			{
				//TODO
			}
			else
			{
				temp = rand() % 25;
				switch (mapInfo[yPos*mapWidth + xPos])
				{
				case TileType::air:
					if (temp == 0)
					{
						temp = rand() % 2;
						mapTileType[yPos*mapWidth + xPos] = 1 + temp;
					}
					else
					{
						mapTileType[yPos*mapWidth + xPos] = 0;
					}
					break;
				case TileType::flowers:
					if (temp == 0)
					{
						temp = rand() % 2;
						mapTileType[yPos*mapWidth + xPos] = 1 + temp;
					}
					else
					{
						mapTileType[yPos*mapWidth + xPos] = 0;
					}
					break;
				case TileType::wall:
					temp = rand() % 5;
					mapTileType[yPos*mapWidth + xPos] = temp + 3;
					break;
				}
			}
			//random flowers mode
		}
	}
	srand(time(NULL));


}

//Update the tile map with the action point sprites
void TileMap::cardActionUpdateMap(CardActionMap cardActionMap)
{
	mapTilesWCardActions = mapTileType;

	//Iterate over each action point
	for (int i = 0; i < cardActionMap.cardActionMap.size(); i++)
	{
		//If its active
		if (cardActionMap.cardActionMap[i].active)
		{
			int tileNo;

			//Update the tilemap
			switch (cardActionMap.cardActionMap[i].attackElement)
			{
			case(AttackElement::ethereal):
				tileNo = 8;
				break;
			case(AttackElement::physical):
				tileNo = 9;
				break;

			default:
				tileNo = 1;
				break;
			}
			mapTilesWCardActions[cardActionMap.cardActionMap[i].yPos*mapWidth + cardActionMap.cardActionMap[i].xPos] = tileNo;
		}
	}
}