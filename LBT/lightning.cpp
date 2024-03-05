// Lightning.cpp
#include "Lightning.h"
#include "game.h"
#include "state.h"

#include <chrono>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>

void drawLightning(SDL_Renderer* renderer, int startX, int startY, int endX, int endY) {

    // Draw the circle at the mouse click location
    filledCircleColor(renderer, endX, endY, 30, 0xBB00FFFF); // Fill circle with yellow color

}
