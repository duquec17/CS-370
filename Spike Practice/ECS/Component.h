#pragma once
#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "GameObject.h"

class Component {
public:
	virtual void print();
	GameObject* gameObject;
};


#endif  /* __COMPONENT_H__ */
