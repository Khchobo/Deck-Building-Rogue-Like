#pragma once

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <unordered_map>
#include <string>
#include <assert.h>
#include "globalVariables.h"
#include <minmax.h>

class Entity
{
public:

	Entity(){}

	sf::Vector2f position;

	void draw(sf::RenderWindow &window);
	void initialise(std::string fileName, sf::Vector2f incomingPosition, ImageManager& imageManager);

	sf::Sprite sprite;
	sf::Texture texture;

	std::string currentAnimation;

	float animationFrameTime;
	int animationFrame;

	sf::Vector2u textureSize;

};