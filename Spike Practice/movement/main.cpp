#include <iostream>
#include <map>
#include <cstdlib>

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL2_framerate.h>
#include <SDL_mixer.h>


#include "state.h"
#include "game.h"
#include "quit.h"

using namespace std;


const int WIDTH = 1600;
const int HEIGHT = 900;

map <string, state *> states;
string current_state = "";
string last_state = "";
state *current_state_ptr = nullptr;


bool transition(string s) {
	bool result = true;
	//leave
	if(current_state_ptr) {
		states[current_state]->leave();
		last_state = current_state;
	};
	//flush
	SDL_Event e;
	while(SDL_PollEvent(&e)); // flush event queue
	//enter
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
	bool quit = false;

	SDL_Window *w = nullptr;
	SDL_Surface *s = nullptr;
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
		cerr << "SDL_Init() fail... " << SDL_GetError() << endl;
		exit(EXIT_FAILURE);
	}

	FPSmanager fps;
	SDL_initFramerate(&fps);


	w = SDL_CreateWindow("Lightning Bolt Town ver:a0.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer *rend = SDL_CreateRenderer(w, -1, 0);

	states["game"] = new game_state(rend);
	states["quit"] = new quit_state(rend, &quit, &last_state);

	transition("game");


	SDL_Event e;
	while(!quit) {
		/* Let even hanadiling update variables needed for drawing*/
		while(SDL_PollEvent(&e)) {

			if(!current_state_ptr || !current_state_ptr->handle_event(e)) {
				switch(e.type){
					case SDL_QUIT: quit = true; break;
					case SDL_KEYDOWN:
						switch(e.key.keysym.sym) {
							case SDLK_ESCAPE:  quit = true;  break;
							default: break;
						} break;
					default: break;
				}
			}
		}

		/* Draw everything that matters */
		SDL_SetRenderDrawColor(rend, 0xCC, 0xEE, 0xFF, 0xFF);
		SDL_RenderClear(rend);
		current_state_ptr->draw();

		SDL_RenderPresent(rend);
		SDL_framerateDelay(&fps);
	}


	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(w);
	SDL_Quit();

	return EXIT_SUCCESS;
}
