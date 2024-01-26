#include <iostream>

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>

#include "game.h"
#include "state.h"

using namespace std;

game_state::game_state(SDL_Renderer *rend) : state(rend) {
	player.w = w / 10;
	player.h = h / 10;
	player.x = (w / 2) - (player.w/2);
	player.y = (h / 2) - (player.h/2);

	strike.w = w / 10;
	strike.h = h / 10;

	go_up = false;
	go_down = false;
	go_left = false;
	go_right = false;
}

game_state::~game_state() {

}

bool game_state::enter() {
	return true;
}
bool game_state::leave() {
	return true;
}

bool game_state::draw() {
	if(go_up) {
		player.y = constrain(player.y - 10, 0, h-player.h);
	}
	if(go_down) {
		player.y = constrain(player.y + 10, 0, h-player.h);
	}
	if(go_left) {
		player.x = constrain(player.x - 10, 0, w-player.w);
	}
	if(go_right) {
		player.x = constrain(player.x + 10, 0, w-player.w);
	}

	SDL_SetRenderDrawColor(rend, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderFillRect(rend, &player);

	return true;
}

bool game_state::handle_event(const SDL_Event &e) {
	bool result = false;
	switch(e.type) {
		case SDL_QUIT:
			transition("quit");
			result = true;
			break;
		case SDL_KEYDOWN:
			switch(e.key.keysym.sym) {
				case SDLK_ESCAPE:
					transition("quit");
					result = true;
					break;
				case SDLK_w:
					go_up = true;
					result = true;
					break;
				case SDLK_s:
					go_down = true;
					result = true;
					break;
				case SDLK_a:
					go_left = true;
					result = true;
					break;
				case SDLK_d:
					go_right = true;
					result = true;
					break;
				default: break;
			} break;
		case SDL_KEYUP:
			switch(e.key.keysym.sym) {
				case SDLK_w:
					go_up = false;
					result = true;
					break;
				case SDLK_s:
					go_down = false;
					result = true;
					break;
				case SDLK_a:
					go_left = false;
					result = true;
					break;
				case SDLK_d:
					go_right = false;
					result = true;
					break;
				default: break;
			} break;
		case SDL_MOUSEBUTTONDOWN:
			SDL_GetMouseState(&mx, &my);
			break;
		default: break;
	}
	return result;
}
