#include "GameObject.h"

transform* GameObject::getTransform() {
	for (Component* c : GameObject::components) {
		if (transform* t = dynamic_cast<transform*>(c)) {
			return t;
		}
	}
	return NULL;
}