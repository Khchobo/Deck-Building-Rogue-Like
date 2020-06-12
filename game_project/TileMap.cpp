#include "TileMap.h"

void TileMap::initialise()
{
	tileSet.loadFromFile("assets/tileset.png");
	vertexMap.setPrimitiveType(sf::Quads);
	vertexMap.resize(mapHeight*mapWidth * 4);
}

void TileMap::updateVertexMap(WindowInfo& windowInfo)
{
	for (unsigned int i = 0; i < mapHeight; i++)
	{
		for (unsigned int j = 0; j < mapWidth; j++)
		{
			int currentTileID = mapTilesWCardActions[i*mapWidth + j];

			int tu = currentTileID % (tileSet.getSize().x / windowInfo.tileSizeInPixels);
			int tv = currentTileID / (tileSet.getSize().x / windowInfo.tileSizeInPixels);

			sf::Vertex* quad =& vertexMap[(i*mapWidth + j) * 4];

			// define its 4 corners
			quad[0].position = sf::Vector2f(j *windowInfo.tileSizeInPixels, i * windowInfo.tileSizeInPixels);
			quad[1].position = sf::Vector2f(j * windowInfo.tileSizeInPixels, (i+1) *windowInfo.tileSizeInPixels);
			quad[2].position = sf::Vector2f((j + 1) * windowInfo.tileSizeInPixels, (i + 1) * windowInfo.tileSizeInPixels);
			quad[3].position = sf::Vector2f((j+1) * windowInfo.tileSizeInPixels, i  * windowInfo.tileSizeInPixels);

			// define its 4 texture coordinates
			quad[0].texCoords = sf::Vector2f(tu * windowInfo.tileSizeInPixels, tv * windowInfo.tileSizeInPixels);
			quad[1].texCoords = sf::Vector2f(tu* windowInfo.tileSizeInPixels, (tv+1) * windowInfo.tileSizeInPixels);
			quad[2].texCoords = sf::Vector2f((tu + 1) * windowInfo.tileSizeInPixels, (tv + 1) * windowInfo.tileSizeInPixels);
			quad[3].texCoords = sf::Vector2f((tu+1) * windowInfo.tileSizeInPixels, tv * windowInfo.tileSizeInPixels);

		}
	}
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	
	states.transform *= getTransform();

	// apply the tileset texture
	states.texture = &tileSet;

	// draw the vertex array
	target.draw(vertexMap, states);
}

void TileMap::defineMapLayout()
{
	int temp;
	srand(layoutSeed);
	for (unsigned int xPos = 0; xPos < mapWidth; xPos++)
	{
		for (unsigned int yPos = 0; yPos < mapHeight; yPos++)
		{
			switch (mapInfo[yPos*mapWidth + xPos])
			{
			case TileType::air:
				temp = rand() % 25;
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
	}
	srand(time(NULL));


}

void TileMap::testDrawPath(AStar::CoordinateList path)
{
	for (auto& coordinate : path) 
	{
		mapTilesWCardActions[coordinate.y*mapWidth + coordinate.x]=9;
	}

}

//Update the tile map with the action point sprites
void TileMap::cardActionUpdateMap(CardActionMap cardActionMap)
{
	mapTilesWCardActions = mapTileType;

	//Iterate over each action point
	for (unsigned int i = 0; i < cardActionMap.cardActionMap.size(); i++)
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
			//TODO give its own texture
			default:
				tileNo = 1;
				break;
			}
			mapTilesWCardActions[cardActionMap.cardActionMap[i].yPos*mapWidth + cardActionMap.cardActionMap[i].xPos] = tileNo;
		}
	}
}