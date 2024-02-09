#pragma once
#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <list>
#include "Component.h"
#include "Transform.h"

class GameObject {
public:
	std::list<Component*> components;

	transform* getTransform();
};

#endif  /* __GAMEOBJECT_H__ */
