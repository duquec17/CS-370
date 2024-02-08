#include <iostream>

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>

#include "quit.h"
#include "state.h"

using namespace std;

quit_state::quit_state(SDL_Renderer *rend, bool *quit, string *last_state) : state(rend) {
	this->quit = quit;
	this->last_state = last_state;

	square.x = w / 3;
	square.y = h / 3;
	square.w = w / 3;
	square.h = h / 3;
}

quit_state::~quit_state() {}


bool quit_state::enter() {
	return true;
}
bool quit_state::leave() {
	return true;
}
bool quit_state::draw() {
	states[*last_state]->draw();
	SDL_SetRenderDrawBlendMode(rend, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(rend, 0x55, 0x55, 0x55, 0x88);
	SDL_RenderFillRect(rend, nullptr);
	SDL_SetRenderDrawBlendMode(rend, SDL_BLENDMODE_NONE);

	SDL_SetRenderDrawColor(rend, 0xFD, 0xCA, 0x86, 0xFF);
	SDL_RenderFillRect(rend, &square);

	stringColor(rend, square.x + (square.w / 4), square.y + (square.h / 3), "Press ENTER to quit.", 0xffffffff);
	stringColor(rend, square.x + (square.w / 4), square.y + (2 * square.h / 3), "Press BACKSPACE to go back.", 0xffffffff);

	return true;
}
bool quit_state::handle_event(const SDL_Event &e) {
	bool result = false;
	switch(e.type){
		case SDL_KEYDOWN:
		switch(e.key.keysym.sym) {
			case SDLK_ESCAPE:
				result = true;
				break;
			case SDLK_RETURN:
				*quit = true;
				break;
			case SDLK_BACKSPACE:
				transition(*last_state);
				result = true;
				break;
			default: break;
		}
		default: break;
	}
	return result;
}
