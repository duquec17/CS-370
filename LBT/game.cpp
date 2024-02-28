#include <iostream>

#include <SDL.h>

#include "headers/game.h"
#include "headers/state.h"
#include "headers/Timer.h"

using namespace std;


inline int constrain(int x, int A, int B) {
	return std::min(std::max((x),A),B);
}

game_state::game_state(SDL_Renderer *rend) : state(rend) {
	player.w = TILE_SIZE;
	player.h = TILE_SIZE;
	player.x = (WINDOW_WIDTH / 2) - (player.w/2);
	player.y = (WINDOW_HEIGHT / 2) - (player.h/2);

	player_vel = 5;

	go_up = false;
	go_down = false;
	go_left = false;
	go_right = false;

	cycle = false;
}

game_state::~game_state() {

}


bool game_state::enter() {
	movement_timer.start();

	return true;
}
bool game_state::leave() {
	return true;
}

bool game_state::draw() {
	//move player
	if(cycle) {
		if(go_up) {
			player.y = constrain(player.y - player_vel, 0, WINDOW_HEIGHT-player.h);
		}
		if(go_down) {
			player.y = constrain(player.y + player_vel, 0, WINDOW_HEIGHT-player.h);
		}
		if(go_left) {
			player.x = constrain(player.x - player_vel, 0, WINDOW_WIDTH-player.w);
		}
		if(go_right) {
			player.x = constrain(player.x + player_vel, 0, WINDOW_WIDTH-player.w);
		}
		cycle = false;
		movement_timer.start();
	}

	//draw player
	SDL_SetRenderDrawColor(renderer, 0xDD, 0xBB, 0xFF, 0xFF);
	SDL_RenderFillRect(renderer, &player);

	return true;
}

bool game_state::handle_event(const SDL_Event &event) {
	bool result = false;
	switch(event.type) {
		case SDL_KEYDOWN:
			switch(event.key.keysym.sym) {
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
			switch(event.key.keysym.sym) {
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
		case SDL_MOUSEBUTTONDOWN: /* currently unused */
			SDL_GetMouseState(&mouse_x, &mouse_y);
			break;
		default: break;
	}
	return result;
}
