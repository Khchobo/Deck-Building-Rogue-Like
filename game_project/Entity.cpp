#include "entities/other/Entity.h"

Entity* Entity::getComponent(std::string _identity)
{
	std::vector<Entity*>::iterator find = std::find_if(components.begin(), components.end(), [&_identity](Entity* component) {return component->identity == _identity; });
	if (find != components.end())
	{
		return *find;
	}
	else
	{
		throw std::invalid_argument("");
	}
}