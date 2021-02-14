#pragma once

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <unordered_map>
#include <string>
#include <assert.h>
#include "globalVariables.h"
#include <minmax.h>
#include <memory>

#define GET_COMPONENT(cast,name) dynamic_cast<cast*>(GetComponent(name).get())
#define GET_PARENT_COMPONENT(cast,name) dynamic_cast<cast*>(parent->GetComponent(name).get())
#define GET_OBJECT_COMPONENT(cast, name, object) dynamic_cast<cast*>(object.GetComponent(name).get())
#define GET_OBJECT_POINTER_COMPONENT(cast, name, object) dynamic_cast<cast*>(object->GetComponent(name).get())

class Entity
{
public:

	Entity(){}
	Entity(std::string identity, ImageManager* imageManager, Entity* parentObject, Entity* rootObject) : m_identity(identity), m_pImageManager(imageManager), m_pParentObject(parentObject), m_pRootObject(rootObject) {}
	virtual ~Entity() {};

	std::shared_ptr <Entity> GetComponent(std::string _identity);

	//The object that created this entity. Will be null pointer if its a root object
	Entity* m_pParentObject;
	//The root of this object. Everything is positioned relative to this.
	Entity* m_pRootObject;
	ImageManager* m_pImageManager;
	std::string m_identity;
	std::vector<std::shared_ptr<Entity>> m_components;
};