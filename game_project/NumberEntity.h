#pragma once
#include "Entity.h"
class NumberEntity :
	public Entity
{
public:
	NumberEntity();
	NumberEntity(float xPos, float yPos, int initialValue);
	void initialise(float xPos, float yPos,int initialValue);
	void draw(sf::RenderWindow& window);

	int value;
private:

	int getNumberOfDigits(int number);
	void storeDigit(std::vector<int>& vectorOfDigits, int recursionDepth, int x);
	std::vector<sf::Texture> digitTextures;
	
};

