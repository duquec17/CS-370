#include <iostream>

#include <SDL.h> //SDL library
#include <SDL2_gfxPrimitives.h> //SDL2_GFX library

#include "game.h" 
#include "state.h" 
#include "Lightning.h" //Include the lightning header file

using namespace std;


inline int constrain(int x, int A, int B) {
	return std::min(std::max((x),A),B);
}

//Lightning condition variables
bool lightningActive = false;
bool lightningAlreadyActive = false;

// Timer callback function
Uint32 timerCallback(Uint32 interval, void* param) {
	lightningActive = false; // Set lightningActive to false after 3 seconds
	lightningAlreadyActive = false;
	return 0;
}


game_state::game_state(SDL_Renderer *rend) : state(rend) {
	player.w = TILE_SIZE;
	player.h = TILE_SIZE;
	player.x = (WINDOW_WIDTH / 2) - (player.w/2);
	player.y = (WINDOW_HEIGHT / 2) - (player.h/2);

	player_vel = 10;

	go_up = false;
	go_down = false;
	go_left = false;
	go_right = false;
}

game_state::~game_state() 
{
}


bool game_state::enter() {
	return true;
}
bool game_state::leave() {
	return true;
}

bool game_state::draw() {
	//move player
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

	//draw player
	SDL_SetRenderDrawColor(renderer, 0xDD, 0xBB, 0xFF, 0xFF);
	SDL_RenderFillRect(renderer, &player);

	//draws lightning circle if lightning state is set as false
	if (lightningActive && !lightningAlreadyActive) {
		// Draw lightning circle
		drawLightning(renderer, 0, 0, mouse_x, mouse_y);
	}

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
		case SDL_MOUSEBUTTONDOWN: 
			if (!lightningActive ) {
				SDL_GetMouseState(&mouse_x, &mouse_y);
				// Set a timer for 2 real-world seconds to set lightningActive to false
				SDL_AddTimer(2000, timerCallback, nullptr);
				lightningActive = true; // Set lightningActive to true when lightning appears
			// Update the flag to indicate that a circle is already active
				result = true;
			}
			break;
		default: break;
	}
	return result;
}
