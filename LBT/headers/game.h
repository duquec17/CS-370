#ifndef __GAME_H__
#define __GAME_H__

#include <SDL.h>
#include <sstream>
#include <cstring>

#include "state.h"
#include "Timer.h"

class game_state : public state {
public:
	//initialization functions
	game_state(SDL_Renderer *renderer);
	~game_state();

	//inherited state functions
	bool enter();
	bool leave();
	bool draw();
	bool handle_event(const SDL_Event &event);

	//new functions
	void createVisualtimer();

	//initialize variables
	const int TILE_SIZE = 50;

	int mouse_x,mouse_y;

	bool go_up;
	bool go_down;
	bool go_left;
	bool go_right;

	SDL_Rect player;
	int player_vel;

	bool cycle;

	SDL_Surface* backgroundSurface;
	SDL_Texture* backgroundTexture;
};

extern Timer movement_timer, survival_timer;

#endif  /* __GAME_H__ */
