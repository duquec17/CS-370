#pragma once
#include "state.h"
class test_state : public state {
public:
	//initialization functions
	test_state(SDL_Renderer* renderer);
	~test_state();

	//inherited state functions
	bool enter();
	bool leave();
	bool draw();
	bool handle_event(const SDL_Event& event);
};