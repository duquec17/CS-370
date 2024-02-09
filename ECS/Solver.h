#pragma once
#ifndef __SOLVER_H__
#define __SOLVER_H__

#include "SDL.h"
#include <stdio.h>

#include "Component.h"
#include "Collider.h"
#include "Collision.h"

class Solver{
public:
	Collider *collA, *collB;

	Solver(Collider* A, Collider* B);
	void computeCollision();
};

#endif  /* __SOLVER_H__ */