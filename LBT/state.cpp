#include <SDL.h>

#include "headers/state.h"

state::state(SDL_Renderer *renderer) {
	this->renderer = renderer;
	SDL_GetRendererOutputSize(renderer, &WINDOW_WIDTH, &WINDOW_HEIGHT);
}
state::~state() {
}
