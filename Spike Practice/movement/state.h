#ifndef __STATE_H__
#define __STATE_H__

#include <iostream>
#include <map>

#include <SDL.h>

bool transition(std::string s);


class state {
public:
	SDL_Renderer *rend;
	int w;
	int h;

	state(SDL_Renderer *rend);
	~state();

	virtual bool enter() = 0;
	virtual bool leave() = 0;
	virtual bool draw() = 0;
	virtual bool handle_event(const SDL_Event &e) = 0;
};

extern std::map <std::string, state *> states;

#endif  /* __STATE_H__ */
