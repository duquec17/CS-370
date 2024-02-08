#include <iostream>

#include <SDL.h>

#include "game.h"
#include "state.h"

using namespace std;

const int TILE_SIZE = 50;

game_state::game_state(SDL_Renderer *rend) : state(rend) {
	player.w = TILE_SIZE;
	player.h = TILE_SIZE;
	player.x = (w / 2) - (player.w/2);
	player.y = (h / 2) - (player.h/2);

	strike.w = w / 10;
	strike.h = h / 10;

	go_up = false;
	go_down = false;
	go_left = false;
	go_right = false;

	for(int i = 0; i < 32; i++) {
		for(int j = 0; j < 18; j++) {
			tiles[i][j] = new tile(TILE_SIZE * i, TILE_SIZE * j);
		}
	}
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

	// for(auto i : tiles)
	// 	i->draw(rend, &player);

	for(int i = 0; i < 32; i++) {
		for(int j = 0; j < 18; j++) {
			tiles[i][j]->draw(rend, &player);
		}
	}

	SDL_SetRenderDrawColor(rend, 0xDD, 0xBB, 0xFF, 0xFF);
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

tile::tile(int X_POS, int Y_POS) {
	t.w = TILE_SIZE;
	t.h = TILE_SIZE;
	t.x = X_POS;
	t.y = Y_POS;
}
bool tile::draw(SDL_Renderer *rend, SDL_Rect *player) {
	SDL_SetRenderDrawColor(rend, 0xCC, 0xEE, 0xFF, 0xFF);
	if(is_in(player)) {
		SDL_SetRenderDrawColor(rend, 0x00, 0xFF, 0x00, 0xFF);
	}
	SDL_RenderFillRect(rend, &t);
	return true;
}
bool tile::is_in(SDL_Rect *player) {
	bool result = false;
	if((player->x == t.x && player->y == t.y) ||
		((player->x > t.x && player->x < (t.x + TILE_SIZE)) ||
		((player->x + TILE_SIZE) > t.x && (player->x + TILE_SIZE) <= (t.x + TILE_SIZE))) &&
		((player->y > t.y && player->y < (t.y+TILE_SIZE)) ||
		((player->y + TILE_SIZE) > t.y && (player->y + TILE_SIZE) <= (t.y + TILE_SIZE)))) {
			result = true;
	}
	return result;
}
