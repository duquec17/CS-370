#include <SDL.h>

// Screen dimensions
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// Rectangle size
const int RECTANGLE_SIZE = 20;

// Object sizes
const int RED_RECT_SIZE = 25;
const int BLUE_RECT_SIZE = 100;
const int BLUE_RECT_WIDTH = 30;

// Initial rectangle position
int rectangleX = SCREEN_WIDTH / 2;
int rectangleY = SCREEN_HEIGHT / 2;

//speed
const int rectangleSpeed = 1; 

// Key press flags
bool wPressed = false;
bool sPressed = false;
bool aPressed = false;
bool dPressed = false;

int main(int argc, char* argv[]) 
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
        return 1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("Moving Rectangle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                         SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!window) 
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }


    ////////////////

    // Define red and blue rectangle positions with random initial locations
    int redX = rand() % (SCREEN_WIDTH - RED_RECT_SIZE);
    int redY = 0; 
    int blueX = rand() % (SCREEN_WIDTH - BLUE_RECT_WIDTH);
    int blueY = rand() % (SCREEN_HEIGHT - BLUE_RECT_SIZE);    


     // Boolean flags for visibility
    bool redVisible = true;
    bool blueVisible = true;


    //////////////////



    // Game loop
    bool running = true;
    while (running) 
    {
        // Handle events
        SDL_Event event;
        while (SDL_PollEvent(&event)) 
        {
            if (event.type == SDL_QUIT) 
            {
                running = false;
            } else if (event.type == SDL_KEYDOWN) 
            {
                switch (event.key.keysym.sym) 
                {
                    case SDLK_w:
                        wPressed = true;
                        break;
                    case SDLK_s:
                        sPressed = true;
                        break;
                    case SDLK_a:
                        aPressed = true;
                        break;
                    case SDLK_d:
                        dPressed = true;
                        break;
                }
            }
         else if (event.type == SDL_KEYUP) 
            {
                switch (event.key.keysym.sym) 
                {
                    case SDLK_w:
                        wPressed = false;
                        break;
                    case SDLK_s:
                        sPressed = false;
                        break;
                    case SDLK_a:
                        aPressed = false;
                        break;
                    case SDLK_d:
                        dPressed = false;
                        break;
                }
            }
        }

        // Update rectangle position 
        if (wPressed && rectangleY > 0) 
        {
            rectangleY -= rectangleSpeed;
        }
        if (sPressed && rectangleY < SCREEN_HEIGHT - RECTANGLE_SIZE)
        {
            rectangleY += rectangleSpeed;
        }
        if (aPressed && rectangleX > 0) 
        {
            rectangleX -= rectangleSpeed;
        }
        if (dPressed && rectangleX < SCREEN_WIDTH - RECTANGLE_SIZE) 
        {
            rectangleX += rectangleSpeed;
        }

        // Clear the screen with black
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw the white rectangle
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_Rect rectangle = {rectangleX, rectangleY, RECTANGLE_SIZE, RECTANGLE_SIZE};
        SDL_RenderFillRect(renderer, &rectangle);
        


///////////////////////////////
       

        // Check for collision
        if (redVisible && blueVisible &&
            rectangleX + RECTANGLE_SIZE >= redX && rectangleX <= redX &&
            rectangleY + RECTANGLE_SIZE >= redY && rectangleY <= redY + RED_RECT_SIZE) 
        {
            blueVisible = false;
        }

        // Draw the red rectangle
        if (redVisible) 
        {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_Rect redRect = {redX, redY, RED_RECT_SIZE, RED_RECT_SIZE};
            SDL_RenderFillRect(renderer, &redRect);
        }

        // Draw the blue rectangle
        if (blueVisible) 
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            SDL_Rect blueRect = {blueX, blueY, BLUE_RECT_WIDTH, BLUE_RECT_SIZE};
            SDL_RenderFillRect(renderer, &blueRect);
        }
        
//////////////////////////////

        // Update the window
        SDL_RenderPresent(renderer);

    }
    // Clean up SDL resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}


