#include "WindowInfo.h"

WindowInfo::WindowInfo()
{
	tileSizeInPixels = pixelSize * tileSize;
}

void WindowInfo::setWindowedWidth(int width)
{
	windowedWidthTiles = width;
	windowedWidthPixels = width * tileSizeInPixels;
}
void WindowInfo::setWindowedHeight(int height)
{
	windowedHeightTiles = height;
	windowedHeightPixels = height * tileSizeInPixels;
}
void WindowInfo::setactiveSceneWidth(int width)
{
	activeSceneWidthTiles = width;
	activeSceneWidthPixels = width * tileSizeInPixels;
}
void WindowInfo::setactiveSceneHeight(int height)
{
	activeSceneHeightTiles = height;
	activeSceneHeightPixels = height * tileSizeInPixels;
}

float WindowInfo::getWindowWidth()
{
	return (fullscreen) ? (float)sf::VideoMode::getDesktopMode().width : (float)windowedWidthPixels;
}

float WindowInfo::getWindowHeight()
{
	return (fullscreen) ? (float)sf::VideoMode::getDesktopMode().height : (float)windowedHeightPixels;
}