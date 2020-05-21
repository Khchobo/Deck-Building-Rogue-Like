#include "NumberEntity.h"
#include <iostream>
#include <assert.h>

NumberEntity::NumberEntity() : digitTextures(10) { initialise(0, 0, 0); }

NumberEntity::NumberEntity(float xPos, float yPos, int initialValue) : digitTextures(10)
{
	initialise(xPos, yPos, initialValue);
}

void NumberEntity::initialise(float x, float y, int initialValue)
{
	for (int i = 0; i < 10; i++)
	{
		assert(digitTextures[i].loadFromFile("assets/numbers_" + std::to_string(i)+".png"));
	}

	//sprite.setTexture(texture);


	value = initialValue;

	xPos = x;
	yPos = y;
}

void NumberEntity::draw(sf::RenderWindow& window)
{
	sf::Sprite finalSprite;
	int numberOfDigits = getNumberOfDigits(value);
	std::vector<int> vectorOfDigits(numberOfDigits);
	storeDigit(vectorOfDigits, 0, value);

	sf::Texture finalTexture;
	assert(finalTexture.create(12*numberOfDigits, 18));
	for (int i = 0; i < numberOfDigits; i++)
	{
		finalTexture.update(digitTextures[vectorOfDigits[i]], 12 * i, 0);
	}
	finalSprite.setTexture(finalTexture);

	//TODO make this work with alignment modes
	finalSprite.setPosition(xPos-finalTexture.getSize().x/2, yPos- finalTexture.getSize().y/2);
	window.draw(finalSprite);



}

void NumberEntity::storeDigit(std::vector<int>& vectorOfDigits, int recursionDepth, int x)
{
	if (x >= 10)
	{
		storeDigit(vectorOfDigits, recursionDepth + 1, x/10);
	}
	int digit = x % 10;
	vectorOfDigits[vectorOfDigits.size()-1-recursionDepth] = digit;
}

int NumberEntity::getNumberOfDigits(int number)
{
	int digits = 0;
	if (number <= 0) { digits = 1;}
	while (number) {
		number /= 10;
		digits++;
	}
	return digits;
}