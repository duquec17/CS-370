// Lightning.cpp
#include "headers/lightning.h"
#include "headers/game.h"
#include "headers/state.h"

#include <chrono>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>

void drawLightning(SDL_Renderer* renderer, int startX, int startY, int endX, int endY) {
    // Draw the circle at the mouse click location
    filledCircleColor(renderer, endX, endY, 30, 0xBB00FFFF); // Fill circle with yellow color

}

void drawLightningCloud(SDL_Renderer* renderer, int startX, int startY, int endX, int endY) {
    // Draw the cursor at the mouse current location
    filledCircleColor(renderer, endX, endY, 30, 0x80808022); //Fill circle with gray
}

