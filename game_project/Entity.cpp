#include "entities/other/Entity.h"

std::shared_ptr<Entity> Entity::getComponent(std::string _identity)
{
	std::vector<std::shared_ptr<Entity>>::iterator find = std::find_if(components.begin(), components.end(), [&_identity](std::shared_ptr<Entity> component) {return component->identity == _identity; });
	if (find != components.end())
	{
		return *find;
	}
	else
	{
		throw std::invalid_argument("");
	}
}