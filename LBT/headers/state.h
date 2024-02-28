#ifndef __STATE_H__
#define __STATE_H__

#include <iostream>
#include <map>

#include <SDL.h>

bool transition(std::string s);


class state {
public:
	SDL_Renderer *renderer;
	int WINDOW_WIDTH;
	int WINDOW_HEIGHT;

	state(SDL_Renderer *renderer);
	~state();

	virtual bool enter() = 0;
	virtual bool leave() = 0;
	virtual bool draw() = 0;
	virtual bool handle_event(const SDL_Event &event) = 0;
};

extern std::map <std::string, state *> states;
extern std::string current_state;
extern std::string last_state;

#endif  /* __STATE_H__ */
