#ifndef __MENU_H__
#define __MENU_H__

#include <SDL.h>

#include "state.h"


class menu_state : public state {
public:
    //initialization functions
	menu_state(SDL_Renderer *renderer);
	~menu_state();

    //inherited state functions
    bool enter();
    bool leave();
    bool draw();
    bool handle_event(const SDL_Event &event);

    //declare variables
    SDL_Rect start_button, quit_button;

    int mouse_x, mouse_y;
};

extern bool quit;

#endif  /* __GAME_H__ */
