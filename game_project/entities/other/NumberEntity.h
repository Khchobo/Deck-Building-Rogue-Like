#pragma once
#include "Sprite.h"
class NumberEntity :
	public Sprite
{
public:
	NumberEntity();
	NumberEntity(sf::Vector2f incomingPosition, int initialValue);

	void Initialise(sf::Vector2f incomingPosition,int initialValue);
	void DrawToScreen(sf::RenderWindow& window, CoordSpace coordSpace = localSpace) override;

	int m_value;
private:

	int GetNumberOfDigits(int number);
	void StoreDigit(std::vector<int>& vectorOfDigits, int recursionDepth, int x);

	std::vector<sf::Texture> m_digitTextures;
	
};

