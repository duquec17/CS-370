#include <SDL.h>

#include "headers/menu.h"
#include "headers/DrawText.h"

using namespace std;


menu_state::menu_state(SDL_Renderer *renderer) : state(renderer) {
    start_button.w = WINDOW_WIDTH / 3;
    start_button.h = WINDOW_HEIGHT / 5;
    start_button.x = (WINDOW_WIDTH/2) - (start_button.w/2);
    start_button.y = (WINDOW_HEIGHT/3) - (start_button.h/2);

    quit_button.w = WINDOW_WIDTH / 3;
    quit_button.h = WINDOW_HEIGHT / 5;
    quit_button.x = (WINDOW_WIDTH/2) - (quit_button.w/2);
    quit_button.y = (WINDOW_HEIGHT/3 * 2) - (quit_button.h/2);
}

menu_state::~menu_state() {
}


bool menu_state::enter() {
    return true;
}

bool menu_state::leave() {
    return true;
}


bool menu_state::draw() {
    SDL_SetRenderDrawColor(renderer, 0xDD, 0xBB, 0xFF, 0xFF);
    SDL_RenderFillRect(renderer, &start_button);

    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(renderer, &quit_button);

    return true;
}

bool menu_state::handle_event(const SDL_Event &event) {
    bool result = false;
    switch(event.type) {
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState(&mouse_x, &mouse_y);
            if(mouse_x >= start_button.x && mouse_x <= (start_button.x + start_button.w) &&
                mouse_y >= start_button.y && mouse_y <= (start_button.y + start_button.h)) {
                transition("game");
            }
            else if(mouse_x >= quit_button.x && mouse_x <= (quit_button.x + quit_button.w) &&
                    mouse_y >= quit_button.y && mouse_y <= (quit_button.y + quit_button.h)) {
                quit = true;
            }
            result = true;
            break;
        default: break;
    }
    return result;
}
