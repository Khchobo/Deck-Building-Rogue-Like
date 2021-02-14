#include "Sprite.h"

void Sprite::Initialise(Entity* _parentObject, Entity* _rootObject, std::string filename, int centering)
{
	m_pParentObject = _parentObject;
	m_pRootObject = _rootObject;
	m_sprite.setTexture(m_pImageManager->getImage(filename + ".png"));
	m_textureSize = (m_pImageManager->getImage(filename + ".png").getSize());
	if (centering == 0)
	{
		m_sprite.setOrigin(sf::Vector2f(m_pImageManager->getImage(filename + ".png").getSize().x*static_cast<float>(0.5)
			, m_pImageManager->getImage(filename + ".png").getSize().y*static_cast<float>(0.5)));
	}
}

void Sprite::DrawToScreen(sf::RenderWindow& window, CoordSpace coordSpace)
{
	PositionalEntity* pPositionalEntity = dynamic_cast<PositionalEntity*>(m_pParentObject);
	sf::Vector2f position =sf::Vector2f(0,0);
	switch (coordSpace)
	{
	case(localSpace):
	{
		PositionalEntity* pWorkingObject = pPositionalEntity;
		position = sf::Vector2f(pWorkingObject->position.x + position.x, pWorkingObject->position.y + position.y);
		while (pWorkingObject != m_pRootObject)
		{
			pWorkingObject = static_cast<PositionalEntity*>(pWorkingObject->m_pParentObject);
			position = sf::Vector2f(pWorkingObject->position.x + position.x, pWorkingObject->position.y + position.y);
		} 
		break;
	}
	case(worldSpace):
		position = sf::Vector2f(0, 0);
		break;
	case(viewportSpace):
		position = sf::Vector2f(pPositionalEntity->position.x-static_cast<signed int>(m_textureSize.x) / 2 - windowInfo.backgroundTexturePosition.x,
								pPositionalEntity->position.y-static_cast<signed int>(m_textureSize.y) / 2 - windowInfo.backgroundTexturePosition.y);
		break;
	default:
		assert(false);
		break;
	}
	m_sprite.setPosition(position.x + m_textureSize.x / 2+ windowInfo.backgroundTexturePosition.x, position.y + m_textureSize.y / 2+ windowInfo.backgroundTexturePosition.y);
	window.draw(m_sprite);
}
