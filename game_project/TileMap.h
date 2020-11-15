#pragma once

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
#include "AStar.hpp"

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
	TileMap() {
	}
	unsigned int pixelSize = 2;

	int layoutSeed;
	//constructor for the tile map
	//mapWidth - number of tiles in horizontal direction
	//mapHeight - number of tiles in vertical direction
	//tileSize - height and width of each tile in pixels
	//map info - array of tile IDs
	//
	TileMap(unsigned int mapWidth, unsigned int mapHeight, unsigned int tileSize, std::vector<TileType> mapInfo, std::vector<std::vector<int>> collision) :

		mapInfo(mapInfo), mapWidth(mapWidth), mapHeight(mapHeight),
		tileSize(tileSize),mapTileType(mapInfo.size())
	{
		srand(static_cast<unsigned int>(time(NULL)));
		layoutSeed = rand();
		defineMapLayout();
	}

	sf::Texture tileSet;
	sf::VertexArray vertexMap;

	void initialise();

	//Creates the map of the room including the tile variations to be drawn by draw()
	void defineMapLayout();

	void cardActionUpdateMap(CardActionMap cardActionMap);

	void testDrawPath(AStar::CoordinateList path);

	void updateVertexMap();

private:

	unsigned int mapWidth, mapHeight, tileSize;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	std::vector<TileType> mapInfo;
	std::vector<int> mapTilesWCardActions;
	std::vector<int> mapTileType;
};