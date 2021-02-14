#include "entities/other/Entity.h"

std::shared_ptr<Entity> Entity::GetComponent(std::string _identity)
{
	std::vector<std::shared_ptr<Entity>>::iterator find = std::find_if(m_components.begin(), m_components.end(), [&_identity](std::shared_ptr<Entity> component) {return component->m_identity == _identity; });
	if (find != m_components.end())
	{
		return *find;
	}
	else
	{
		throw std::invalid_argument("");
	}
}