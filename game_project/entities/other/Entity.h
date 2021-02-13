#pragma once

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <unordered_map>
#include <string>
#include <assert.h>
#include "globalVariables.h"
#include <minmax.h>
#include <memory>

#define GET_COMPONENT(cast,name) dynamic_cast<cast*>(getComponent(name))
#define GET_PARENT_COMPONENT(cast,name) dynamic_cast<cast*>(parent->getComponent(name))
#define GET_OBJECT_COMPONENT(cast, name, object) dynamic_cast<cast*>(object.getComponent(name))

class Entity
{
public:

	Entity(){}
	Entity(std::string identity, ImageManager* imageManager) : identity(identity), imageManager(imageManager) {}
	virtual ~Entity();

	ImageManager* imageManager;
	std::string identity;
	std::vector<Entity*> components;

	Entity* getComponent(std::string _identity);
};