#pragma once

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <unordered_map>
#include <string>
#include <assert.h>
#include "Animation.h"
#include "globalVariables.h"
#include <minmax.h>

class Entity
{
public:

	Entity(){}

	sf::Vector2f position;

	void draw(sf::RenderWindow &window, ImageManager& imageManager);
	void initialise(std::string fileName, sf::Vector2f incomingPosition,bool offset, ImageManager& imageManager);

	void animationUpdate(ImageManager imageManager);
	void animationNew(std::string name);

	sf::Sprite sprite;
	sf::Texture texture;
    
	//maps the title of each animation onto its animation class instance
	std::unordered_map<std::string,Animation> animationMap;

	std::string currentAnimation;

	float animationFrameTime;
	int animationFrame;

	sf::Vector2u textureSize;

	int alignment;

};