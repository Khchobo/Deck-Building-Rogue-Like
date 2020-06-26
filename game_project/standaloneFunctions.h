#include <algorithm>
#include "globalVariables.h"
#include <vector>
#include <string>
#include "WindowInfo.h"
#include <stdexcept>
#include "json/json.h"
#include <fstream>

#ifndef STANDALONE_H
#define STANDALONE_H

namespace standaloneFunctions {

	enum class CharType {player,enemy};
	
	enum class Alignment {left, right, centre, top, bottom};
	enum class Axis {x,y};

	float easeInOut(float x);
	std::vector<sf::Vector2i> lineOfSight(int x, int y, int x2, int y2);

	Json::Value loadJsonFile(const char* filename);

	/**
	*Returns the quadratic formula -a*x^2+ax between x=0 and x=1. Used to give a vertical offset when moving
	*Based upon move percentage
	*/
	float quadraticHop(float a, float x);

	/**
	*Gives a position in the window in pixels based on an offset given in tiles from a
	*particular side of the screen. This function will automatically handle fullscreen
	*or windowed mode
	*
	*@param alignment The point on the screen to offset from. Can only take the following enum values:
	*'Alignment::top', 'Alignment::centre', 'Alignment::bottom, 'Alignment::left', 'Alignment::right'
	*
	*@param axis The axis of the coordinate to be returned. Can only take enum values 'Axis::x', 'Axis::y'
	*@param offset The offset from the alignment position, given in tiles
	*@return The coordinate along the axis given in pixels
	*/
	float setPosition(Alignment alignment, Axis axis, float offset, WindowInfo windowInfo);
	/**
	*Gives a position in the window in pixels based on an offset given in tiles from a
	*particular side of the screen. This function will automatically handle fullscreen
	*or windowed mode
	*
	*@param alignment The point on the screen along parameter 'axis' to offset from, given in pixels.
	*
	*
	*@param axis The axis of the coordinate to be returned. Can only take values 'x', 'y'
	*@param offset The offset from the alignment position, given in tiles
	*@return The coordinate along the axis given in pixels
	*/
	float setPosition(float alignment, Axis axis, float offset, WindowInfo windowInfo);

	float setWindowSize(Axis axis, WindowInfo windowInfo);

}

#endif