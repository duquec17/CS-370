#include <iostream>

#include <SDL.h>

#include "headers/teststate.h"
#include "headers/state.h"

using namespace std;

test_state::test_state(SDL_Renderer* rend) : state(rend) {
	printf("Constructing state.\n");
}

test_state::~test_state() {
	printf("Deconstructing state.\n");
}


bool test_state::enter() {
	printf("Entering state.\n");
	return true;
}
bool test_state::leave() {
	printf("Exiting state.\n");
	return true;
}

bool test_state::draw() {
	//move player
	return true;
}

bool test_state::handle_event(const SDL_Event& event) {
	bool result = false;
	printf("Handling event.\n");
	return result;
}
