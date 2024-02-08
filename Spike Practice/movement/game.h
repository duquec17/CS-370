#ifndef __GAME_H__
#define __GAME_H__

#include <SDL.h>

#include "state.h"


class tile {
public:
	tile(int X_POS, int Y_POS);
	~tile();

	bool draw(SDL_Renderer *rend, SDL_Rect *player);
	bool is_in(SDL_Rect *player);

	SDL_Rect t;
};


class game_state : public state {
public:
	game_state(SDL_Renderer *rend);
	~game_state();

	bool enter();
	bool leave();
	bool draw();

	bool handle_event(const SDL_Event &e);

	int mx,my;
	bool go_up;
	bool go_down;
	bool go_left;
	bool go_right;

	SDL_Rect player;
	SDL_Rect strike;

	tile* tiles[32][18];
};

inline int constrain(int x, int A, int B) {
	return std::min(std::max((x),A),B);
}

#endif  /* __GAME_H__ */
