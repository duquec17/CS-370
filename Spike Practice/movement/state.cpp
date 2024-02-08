#include <SDL.h>

#include "state.h"

state::state(SDL_Renderer *rend) {
	this->rend = rend;
	SDL_GetRendererOutputSize(rend, &w, &h);
}
state::~state() {
}
