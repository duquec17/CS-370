#pragma once
#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include "SDL.h"
#include <stdio.h>

#include "Component.h"

class transform:Component {
public:
	SDL_Point position;
	float rotation;
};

#endif  /* __TRANSFORM_H__ */