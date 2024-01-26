#ifndef __GAME_H__
#define __GAME_H__

#include <SDL.h>

#include "state.h"


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
};

inline int constrain(int x, int A, int B) {
	return std::min(std::max((x),A),B);
}

#endif  /* __GAME_H__ */
