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
	return (fullscreen) ? sf::VideoMode::getDesktopMode().width : windowedWidthPixels;
}

float WindowInfo::getWindowHeight()
{
	return (fullscreen) ? sf::VideoMode::getDesktopMode().height : windowedHeightPixels;
}