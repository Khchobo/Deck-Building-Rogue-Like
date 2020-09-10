#pragma once
#include "Sprite.h"
class NumberEntity :
	public Sprite
{
public:
	NumberEntity();
	NumberEntity(sf::Vector2f incomingPosition, int initialValue);
	void initialise(sf::Vector2f incomingPosition,int initialValue);
	void draw(sf::RenderWindow& window);

	int value;
private:

	int getNumberOfDigits(int number);
	void storeDigit(std::vector<int>& vectorOfDigits, int recursionDepth, int x);
	std::vector<sf::Texture> digitTextures;
	
};

