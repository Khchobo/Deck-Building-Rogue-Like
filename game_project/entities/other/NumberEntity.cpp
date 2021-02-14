#include "NumberEntity.h"
#include <iostream>
#include <assert.h>

NumberEntity::NumberEntity() : m_digitTextures(10) { Initialise(sf::Vector2f(0,0), 0); }

NumberEntity::NumberEntity(sf::Vector2f incomingPosition, int initialValue) : m_digitTextures(10)
{
	Initialise(incomingPosition, initialValue);
}

void NumberEntity::Initialise(sf::Vector2f incomingPosition, int initialValue)
{
	for (int i = 0; i < 10; i++)
	{
		bool ok = m_digitTextures[i].loadFromFile("assets/numbers_" + std::to_string(i) + ".png");
		assert(ok);
	}

	m_value = initialValue;
	//position = std::make_shared<sf::Vector2f>(incomingPosition);
}

void NumberEntity::DrawToScreen(sf::RenderWindow& window, CoordSpace coordSpace)
{
	int numberOfDigits = GetNumberOfDigits(m_value);
	std::vector<int> vectorOfDigits(numberOfDigits);
	StoreDigit(vectorOfDigits, 0, m_value);

	assert(m_texture.create(12*numberOfDigits, 18));
	for (int i = 0; i < numberOfDigits; i++)
	{
		m_texture.update(m_digitTextures[vectorOfDigits[i]], 12 * i, 0);
	}
	m_sprite.setTexture(m_texture);
	m_textureSize = m_texture.getSize();

	//Sprite::draw(window, viewportSpace);
}

void NumberEntity::StoreDigit(std::vector<int>& vectorOfDigits, int recursionDepth, int x)
{
	if (x >= 10)
	{
		StoreDigit(vectorOfDigits, recursionDepth + 1, x/10);
	}
	int digit = x % 10;
	vectorOfDigits[vectorOfDigits.size()-1-recursionDepth] = digit;
}

int NumberEntity::GetNumberOfDigits(int number)
{
	int digits = 0;
	if (number <= 0) { digits = 1;}
	while (number) {
		number /= 10;
		digits++;
	}
	return digits;
}