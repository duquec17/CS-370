// Lightning.cpp
#include "Lightning.h"
#include "game.h"
#include "state.h"
#include <SDL.h>

void drawLightning(SDL_Renderer* renderer, int startX, int startY, int endX, int endY) {
    // Clear the renderer

    // Draw the box at the mouse click location
    SDL_Rect box;
    box.x = endX - 25; // Adjust for centering
    box.y = endY - 25; // Adjust for centering
    box.w = 50;
    box.h = 50;
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Yellow color
    SDL_RenderFillRect(renderer, &box);
}

int main() {
    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Draw Box on Click", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool quit = false;
    SDL_Event event;

    while (!quit) {
        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    // Update the coordinates of the box when left mouse button is clicked
                    drawLightning(renderer, 0, 0, event.button.x, event.button.y);
                }
            }
        }
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
