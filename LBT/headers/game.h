#ifndef __GAME_H__
#define __GAME_H__

#include <SDL.h>

#include "state.h"
#include "Timer.h"


typedef struct tile tile;
struct tile {
	SDL_Rect rect;
	bool is_water;
	bool is_wall;
};


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

	//initialize variables
	const int TILE_SIZE = 40;

	tile map[32][18];

	int mouse_x,mouse_y;

	bool go_up;
	bool go_down;
	bool go_left;
	bool go_right;

	SDL_Rect player;
	int player_vel;

	bool cycle;
};

extern Timer movement_timer;

#endif  /* __GAME_H__ */
