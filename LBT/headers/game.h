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
	int strike_x, strike_y;

	bool go_up;
	bool go_down;
	bool go_left;
	bool go_right;

	SDL_Rect player;
	int player_vel;

	// Cloud Cursor sprite variables
	int XCNT = 6;
	int YCNT = 20;
	//const int TCNT = XCNT * YCNT;
	int cscnt = 0;
	int CW;
	int CH;
	SDL_Texture* Cursorsprite;
	SDL_Rect cursorAnim[6];

	// Lightning strike sprite variables
	const int FCNT = 16;
	int scnt = 0;
	int W;
	int H;
	SDL_Texture* Lsprite;
	SDL_Rect lightAnim[20];

	bool cycle;

};

extern Timer movement_timer, survival_timer;
extern bool quit;

#endif  /* __GAME_H__ */
