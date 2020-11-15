#include "NumberEntity.h"
#include <iostream>
#include <assert.h>

NumberEntity::NumberEntity() : digitTextures(10) { initialise(sf::Vector2f(0,0), 0); }

NumberEntity::NumberEntity(sf::Vector2f incomingPosition, int initialValue) : digitTextures(10)
{
	initialise(incomingPosition, initialValue);
}

void NumberEntity::initialise(sf::Vector2f incomingPosition, int initialValue)
{
	for (int i = 0; i < 10; i++)
	{
		assert(digitTextures[i].loadFromFile("assets/numbers_" + std::to_string(i)+".png"));
	}

	value = initialValue;
	position = incomingPosition;
}

void NumberEntity::draw(sf::RenderWindow& window, CoordSpace coordSpace, const PositionalEntity* parent)
{
	int numberOfDigits = getNumberOfDigits(value);
	std::vector<int> vectorOfDigits(numberOfDigits);
	storeDigit(vectorOfDigits, 0, value);

	assert(texture.create(12*numberOfDigits, 18));
	for (int i = 0; i < numberOfDigits; i++)
	{
		texture.update(digitTextures[vectorOfDigits[i]], 12 * i, 0);
	}
	sprite.setTexture(texture);
	textureSize = texture.getSize();

	Sprite::draw(window, viewportSpace);
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