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

	float xPos;
	float yPos;
	void draw(sf::RenderWindow &window);
	void initialise(std::string fileName,float xPos,float yPos,bool offset);

	void animationUpdate();
	void animationNew(std::string name);

	sf::Sprite sprite;
	sf::Texture texture;
    
	//maps the title of each animation onto its animation class instance
	std::unordered_map<std::string,Animation> animationMap;

	std::string currentAnimation;
	float animationFrameTime;
	int animationFrame;

};