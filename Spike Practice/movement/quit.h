#ifndef __QUIT_H__
#define __QUIT_H__

#include <SDL.h>

#include "state.h"


class quit_state : public state {
public:
	quit_state(SDL_Renderer *rend, bool *quit, std::string *last_state);
	~quit_state();

	bool enter();
	bool leave();
	bool draw();

	bool handle_event(const SDL_Event &e);

	bool *quit;
	std::string *last_state;

	SDL_Rect square;
};

#endif  /* __QUIT_H__ */
