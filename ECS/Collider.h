#pragma once
#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include "Component.h"

class Collider:public Component {
public:
	int width, height;
};

#endif  /* __COLLIDER_H__ */

