#pragma once
#include "SFML\Graphics.hpp"

class WindowInfo
{
public:
	WindowInfo();
	const int pixelSize = 2, tileSize = 16;
	//the product of the above, the size of a tile in absolute pixels
	int tileSizeInPixels;

	int fullscreen = 1;

	//windowed width and height is the size of the window when not in fullscreen mode
	int windowedWidthTiles, windowedHeightTiles, windowedWidthPixels, windowedHeightPixels;
	//size of the rendered part of the battle area, i.e. excluding the UI boxes.
	int activeSceneWidthTiles, activeSceneHeightTiles, activeSceneHeightPixels, activeSceneWidthPixels;

	//The width and height of the UI boxes. Always given in TILES
	int UIWidth, UIHeight;

	//using set functions so that we can
	//simutaneously change both the value
	//in pixels and in tiles and these can be
	//independently accessed depending on need
	void setWindowedWidth(int width);
	void setWindowedHeight(int height);
	void setactiveSceneWidth(int width);
	void setactiveSceneHeight(int height);

	float getWindowWidth();
	float getWindowHeight();
};

