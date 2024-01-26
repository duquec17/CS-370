#include <SDL.h>
// #include <iostream>

#include "state.h"

state::state(SDL_Renderer *rend) {
	this->rend = rend;
	SDL_GetRendererOutputSize(rend, &w, &h);
	// std::cout << "Made a State" << std::endl;
}
state::~state() {
	// std::cout << "Destroyed a State" << std::endl;
}
