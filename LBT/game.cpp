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

	for(int i = 0; i < WINDOW_WIDTH / TILE_SIZE; i++) {
		for (int j = 0; j < WINDOW_HEIGHT / TILE_SIZE; j++) {
			tile t;
			SDL_Rect r(i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE);
			t.rect = r;
			t.is_water = false;
			t.is_wall = false;
			map[i][j] = t;
		}
	}

	cycle = false;
}

game_state::~game_state() {

}


bool game_state::enter() {
	movement_timer.start();
	survival_timer.start();

	map[31][17].is_wall = true;

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
	}

	//draw map
	for(auto i : reinterpret_cast<tile (&)[sizeof(map) / sizeof(**map)]>(map)) {
		if(i.is_water)
			SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF); \
		else if(i.is_wall)
			SDL_SetRenderDrawColor(renderer, 0x88, 0x88, 0x88, 0xFF);
		else
			SDL_SetRenderDrawColor(renderer, 0xCC, 0xEE, 0xFF, 0xFF);
		SDL_RenderFillRect(renderer, &i.rect);
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
