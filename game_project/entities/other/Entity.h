#pragma once

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <unordered_map>
#include <string>
#include <assert.h>
#include "globalVariables.h"
#include <minmax.h>
#include <memory>

#define GET_COMPONENT(cast,name) dynamic_cast<cast*>(getComponent(name).get())
#define GET_PARENT_COMPONENT(cast,name) dynamic_cast<cast*>(parent->getComponent(name).get())
#define GET_OBJECT_COMPONENT(cast, name, object) dynamic_cast<cast*>(object.getComponent(name).get())
#define GET_OBJECT_POINTER_COMPONENT(cast, name, object) dynamic_cast<cast*>(object->getComponent(name).get())

class Entity
{
public:

	Entity(){}
	Entity(std::string identity, ImageManager* imageManager, Entity* parentObject, Entity* rootObject) : identity(identity), imageManager(imageManager), parentObject(parentObject), rootObject(rootObject) {}
	virtual ~Entity() {};

	//The object that created this entity. Will be null pointer if its a root object
	Entity* parentObject;
	//The root of this object. Everything is positioned relative to this.
	Entity* rootObject;
	ImageManager* imageManager;
	std::string identity;
	std::vector<std::shared_ptr<Entity>> components;

	std::shared_ptr <Entity> getComponent(std::string _identity);
};