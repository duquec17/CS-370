#include <iostream>
#include <map>
#include <cstdlib>

#include <SDL.h>
// #include <SDL2_gfxPrimitives.h>
// #include <SDL2_framerate.h>
#include <SDL_mixer.h>


#include "headers/state.h"
#include "headers/game.h"

using namespace std;


const int WIDTH = 1280;
const int HEIGHT = 720;

/* public variables for all states */
map <string, state *> states;
string current_state = "";
string last_state = "";
state *current_state_ptr = nullptr;

bool quit = false;


void cycle_mvt() {
	if(current_state == "game")
		dynamic_cast<game_state *>(current_state_ptr)->cycle = true;
}
void endGame() {
	quit = true;
}
Timer
movement_timer(cycle_mvt, 25, -1, Timer::OnComplete::RESTART),
survival_timer(endGame, 10000, 1000, Timer::OnComplete::STOP);



bool transition(string s) {
	bool result = true;
	//leave state
	if(current_state_ptr) {
		states[current_state]->leave();
		last_state = current_state;
	};
	//flush
	SDL_Event event;
	while(SDL_PollEvent(&event)); // flush event queue
	//enter state
	if(states.contains(s)) {
		current_state_ptr = states[s];
		current_state = s;
		current_state_ptr->enter();
	}
	else {
		cerr << "OH NO!!! " << s << " is not a valid state." << endl;
		result = false;
		exit(EXIT_FAILURE);
	}

	return result;
}


int main(int argc, char *argv[]) {

	SDL_Window *window = nullptr;
	SDL_Surface *surface = nullptr;
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
		cerr << "SDL_Init() fail... " << SDL_GetError() << endl;
		exit(EXIT_FAILURE);
	}

	// FPSmanager fps;
	// SDL_initFramerate(&fps);


	window = SDL_CreateWindow("Lightning Bolt Town ver:a0.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

	/* create all states */
	states["game"] = new game_state(renderer);
	/* transistion to initial state */
	transition("game");


	SDL_Event event;
	while(!quit) {
		/* let event hanadiling update variables needed for drawing */
		while(SDL_PollEvent(&event)) {
			if(!current_state_ptr || !current_state_ptr->handle_event(event)) {
				/* handle events not handled by current state */
				switch(event.type){
					case SDL_QUIT: quit = true; break;
					case SDL_KEYDOWN:
						switch(event.key.keysym.sym) {
							case SDLK_ESCAPE:  quit = true;  break;
							default: break;
						} break;
					default: break;
				}
			}
		}

		/* draw everything that matters */
		SDL_SetRenderDrawColor(renderer, 0xCC, 0xEE, 0xFF, 0xFF);
		SDL_RenderClear(renderer);
		current_state_ptr->draw();

		SDL_RenderPresent(renderer);
		// SDL_framerateDelay(&fps);
	}


	movement_timer.stop();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS;
}
