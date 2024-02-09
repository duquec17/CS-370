#include "Solver.h"

void Solver::computeCollision() {
	transform 
		*transformA = collA->gameObject->getTransform(),
		*transformB = collB->gameObject->getTransform();

    float
        bottomA = transformA->position.y - collA->height / 2,
        topA = transformA->position.y + collA->height / 2,
        leftA = transformA->position.x - collA->width / 2,
        rightA = transformA->position.x + collA->width / 2,

        bottomB = transformB->position.y - collB->height / 2,
        topB = transformB->position.y + collB->height / 2,
        leftB = transformB->position.x - collB->width / 2,
        rightB = transformB->position.x + collB->width / 2;

    if (bottomA <= topB)
    {
        return false;
    }

    if (topA >= bottomB)
    {
        return false;
    }

    if (rightA <= leftB)
    {
        return false;
    }

    if (leftA >= rightB)
    {
        return false;
    }

    //If none of the sides from A are outside B
	return NULL;
}