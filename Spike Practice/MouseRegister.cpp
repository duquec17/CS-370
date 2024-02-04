//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <chrono>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int TILE_SIZE = 32;
const int ROWS = SCREEN_HEIGHT / TILE_SIZE;
const int COLS = SCREEN_WIDTH / TILE_SIZE;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

int tiles[ROWS][COLS] = { 0 };  // 2D array to represent tiles
int hoverTilesRow = -1;
int hoverTilesCol = -1;
//std::chrono::time_point<std::chrono::steady_clock> hoverStartTime;
std::chrono::time_point<std::chrono::steady_clock> clickStartTime;


void initSDL() {
    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Create window
    window = SDL_CreateWindow("2D Array Tiles Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void closeSDL() {
    // Destroy window and renderer
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    // Quit SDL
    SDL_Quit();
}

void drawTiles() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // Set draw color to white

    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
           
            //Variable for rectangle
            SDL_Rect tileRect = { col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE};

            //Draw Tile Outline
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &tileRect);

            //Draw Tile
            if (tiles[row][col] == 1) {
                //If tile is marked fill it with a different color
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

                //Check to see if it's time to revert tile to color after 5 seconds
                auto currentTime = std::chrono::steady_clock::now();
                auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - clickStartTime).count();
                if (elapsedTime >= 3) {
                    //Reverts color
                    tiles[row][col] = 0;
                }
            } else if (row == hoverTilesRow && col == hoverTilesCol) {
                //If mouse is hovering over tile fill with temporary grey color
                SDL_SetRenderDrawColor(renderer, 169, 169, 169, 255);

            } else {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            }

            SDL_RenderFillRect(renderer, &tileRect);
        }
    }
}

int main(int argc, char* args[]) {
    initSDL();

    SDL_Event e;
    bool quit = false;

    while (!quit) {
        // Handle events
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN) {
                // Mark the clicked tile
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                int clickedRow = mouseY / TILE_SIZE;
                int clickedCol = mouseX / TILE_SIZE;

                if (clickedRow >= 0 && clickedRow < ROWS && clickedCol >= 0 && clickedCol < COLS) {
                    tiles[clickedRow][clickedCol] = 1;

                    //Set the timer for reverting the color
                    clickStartTime = std::chrono::steady_clock::now();
                }
            }
            else if (e.type == SDL_MOUSEMOTION) {
                //Update hoverTilesRow and hoverTilesCol
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                hoverTilesRow = mouseY / TILE_SIZE;
                hoverTilesCol = mouseX / TILE_SIZE;
            }
        }

        // Clear the renderer
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Draw tiles
        drawTiles();

        // Update the renderer
        SDL_RenderPresent(renderer);
    }

    closeSDL();

    return 0;
}