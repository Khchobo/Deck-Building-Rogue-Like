#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include <thread>
#include <assert.h>
#include <time.h>
#include "TileType.h"
#include "CardActionMap.h"

class TileMap
{
public:
	TileMap() {
	}
	unsigned int pixelSize = 2;

	//use predefined flower positions or random
	bool setFlowers = false;
	int layoutSeed;
	std::vector<sf::Image> spriteImages;
	std::vector<sf::Uint8> pixels;
	unsigned int mapWidth, mapHeight, tileSize;
	sf::VertexArray quads;
	//constructor for the tile map
	//mapWidth - number of tiles in horizontal direction
	//mapHeight - number of tiles in vertical direction
	//tileSize - height and width of each tile in pixels
	//map info - array of tile IDs
	//
	TileMap(unsigned int mapWidth, unsigned int mapHeight, unsigned int tileSize, std::vector<TileType> mapInfo) :
		mapInfo(mapInfo), mapWidth(mapWidth), mapHeight(mapHeight), tileSize(tileSize), spriteImages(10),mapTileType(mapInfo.size())
	
	{
		srand(time(NULL));
		layoutSeed = rand();
		initiateMap();
	}


	
	void initialise();

	//Creates the map of the room including the tile variations to be drawn by draw()
	void initiateMap();

	void cardActionUpdateMap(CardActionMap cardActionMap);

	virtual void draw(sf::Texture& texture) const;
private:
	std::vector<TileType> mapInfo;
	std::vector<int> mapTilesWActionPoints;
	std::vector<int> mapTileType;
};