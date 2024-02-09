#pragma once
#ifndef __COLLISION_H__
#define __COLLISION_H__

#include "SDL.h"
#include <stdio.h>

#include "Component.h"
#include "Collider.h"

//Collision is a means of storing data about a given data to be passed to the colliding object's "OnCollision" callback.

class Collision{
public:
	Collision(Collider *A, Collider *B);
	Collider *A, *B;
};

#endif  /* __COLLISION_H__ */