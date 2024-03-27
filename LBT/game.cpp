#include <iostream>

#include <SDL.h> //SDL library
#include <SDL_image.h>
#include <SDL2_gfxPrimitives.h> //SDL2_GFX library

#include "headers/game.h"
#include "headers/state.h"
#include "headers/Timer.h"
#include "headers/lightning.h"

using namespace std;


inline int constrain(int x, int A, int B) {
	return std::min(std::max((x),A),B);
}

// Lightning condition variables
bool lightningActive = false;
bool lightningAlreadyActive = false;
bool playerAlive = true;


// Timer callback function
Uint32 timerCallback(Uint32 interval, void* param) {
	lightningActive = false; // Set lightningActive to false after 3 seconds
	lightningAlreadyActive = false;
	return 0;
}


game_state::game_state(SDL_Renderer *rend) : state(rend) {
	player.w = TILE_SIZE;
	player.h = TILE_SIZE;
	player.x = (WINDOW_WIDTH / 2) - (player.w/2);
	player.y = (WINDOW_HEIGHT / 2) - (player.h/2);

	player_vel = 5;

	go_up = false;
	go_down = false;
	go_left = false;
	go_right = false;

	for(int i = 0; i < WINDOW_WIDTH / TILE_SIZE; i++) {
		for (int j = 0; j < WINDOW_HEIGHT / TILE_SIZE; j++) {
			tile t;
			SDL_Rect r(i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE);
			t.rect = r;
			t.is_water = false;
			t.is_wall = false;
			map[i][j] = t;
		}
	
	}

	//Loading Lightning cursor location
	SDL_Surface* Csprite_s = IMG_Load("CSSheet.png");
	if (Csprite_s) {
		cout << "Cloud cursor sprite acquired" << endl;
	}
	CW = Csprite_s->w / XCNT;
	CH = Csprite_s->h / YCNT;

	//Converts Surface into texture for cursor Icon
	Cursorsprite = SDL_CreateTextureFromSurface(renderer, Csprite_s);
	SDL_FreeSurface(Csprite_s);

	for (int i = 0, x = 0, y = 2; x < XCNT; x++) {
		SDL_Rect& c = cursorAnim[i++];
		c.w = CW;
		c.h = CH;
		c.y = y * CH;
		c.x = x * CW;
	}

	//Loading Lightning strike Sprite sheet
	SDL_Surface* Lsprite_s = IMG_Load("LEXSheet.png"); //Uses LSSheet.png
	if (Lsprite_s) {
		cout << "Lightning strike sprite acquired" << endl;
	}
	W = Lsprite_s->w / FCNT;
	H = Lsprite_s->h;

	//Converts Surface into texture for Lightning strike
	Lsprite = SDL_CreateTextureFromSurface(renderer, Lsprite_s);
	SDL_FreeSurface(Lsprite_s);

	
	for (int i = 0, x = 0; x < FCNT; x++) {
		SDL_Rect& r = lightAnim[i++];
		r.w = W;
		r.h = H;
		r.y = 0;
		r.x = x * W;
	}

	cycle = false;
}

game_state::~game_state()
{
}


bool game_state::enter() {
	movement_timer.start();
	survival_timer.start();

	map[0][0].is_water = true;
	map[0][1].is_water = true;
	map[1][0].is_water = true;
	map[1][1].is_water = true;

	map[31][17].is_wall = true;

	return true;
}
bool game_state::leave() {
	return true;
}

bool game_state::draw() {
	//move player
	if(cycle) {
		if(go_up) {
			player.y = constrain(player.y - player_vel, 0, WINDOW_HEIGHT-player.h);
		}
		if(go_down) {
			player.y = constrain(player.y + player_vel, 0, WINDOW_HEIGHT-player.h);
		}
		if(go_left) {
			player.x = constrain(player.x - player_vel, 0, WINDOW_WIDTH-player.w);
		}
		if(go_right) {
			player.x = constrain(player.x + player_vel, 0, WINDOW_WIDTH-player.w);
		}
		cycle = false;
	}

	//draw map
	for(auto i : reinterpret_cast<tile (&)[sizeof(map) / sizeof(**map)]>(map)) {
		if(i.is_water)
			SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF); \
		else if(i.is_wall)
			SDL_SetRenderDrawColor(renderer, 0x88, 0x88, 0x88, 0xFF);
		else
			SDL_SetRenderDrawColor(renderer, 0xCC, 0xEE, 0xFF, 0xFF);
		SDL_RenderFillRect(renderer, &i.rect);
	}
  
	//Lightning vars
	int lightRadius = 40;

	//draw player if it's not hit by the lightning
	if (!lightningAlreadyActive) {
		SDL_SetRenderDrawColor(renderer, 0xDD, 0xBB, 0xFF, 0xFF);
		SDL_RenderFillRect(renderer, &player);
	}

	// Draw cursor if click hasn't been made
	if (!lightningActive) {
		// Draw the lightning cloud at the cursor position
		drawLightningCloud(renderer, 0, 0, mouse_x, mouse_y);

		// Makes ligthning cloud animation appear
			//Makes the actual Llightning strike animation appear 
		if (cscnt < XCNT) {
			SDL_Rect j{ mouse_x - ((lightRadius * 1.5) / 2),  mouse_y - ((lightRadius * 1.5) / 2), lightRadius *1.5, lightRadius *1.5};
			SDL_RenderCopy(renderer, Cursorsprite, &cursorAnim[cscnt++], &j);
			cout << "Cloud Running" << endl;
		}
		else
		{
			cscnt = 0;
		}
	}

	//draws lightning circle if lightning state is set as false
	if (lightningActive && !lightningAlreadyActive) {
		bool hitPlayer = false; // Flag to track if the circle has hit the player
		// Calculate the distances between each corner of the player's square and the center of the circle
		int playerTopLeftX = player.x;
		int playerTopLeftY = player.y;
		int playerTopRightX = player.x + player.w;
		int playerTopRightY = player.y;
		int playerBottomLeftX = player.x;
		int playerBottomLeftY = player.y + player.h;
		int playerBottomRightX = player.x + player.w;
		int playerBottomRightY = player.y + player.h;
			drawLightning(renderer, 0, 0, strike_x, strike_y);
			drawLightning(renderer, 0, 0, strike_x, strike_y);
		double topLeftDistance = sqrt(pow(playerTopLeftX - strike_x, 2) + pow(playerTopLeftY - strike_y, 2));
		double topRightDistance = sqrt(pow(playerTopRightX - strike_x, 2) + pow(playerTopRightY - strike_y, 2));
		double bottomLeftDistance = sqrt(pow(playerBottomLeftX - strike_x, 2) + pow(playerBottomLeftY - strike_y, 2));
		double bottomRightDistance = sqrt(pow(playerBottomRightX - strike_x, 2) + pow(playerBottomRightY - strike_y, 2));
		// Check if any of the distances are less than or equal to the radius of the circle
		if (topLeftDistance <= lightRadius || topRightDistance <= lightRadius ||
			bottomLeftDistance <= lightRadius || bottomRightDistance <= lightRadius) {
			hitPlayer = true; // Set the flag indicating that the circle has hit the player
			lightningAlreadyActive = true; // Set lightningAlreadyActive to true to prevent further drawing of the circle
			playerAlive = false;
		}

		// Draw lightning circle if it's not on top of the player
		if (lightningActive && !lightningAlreadyActive) {
			drawLightning(renderer, 0, 0, strike_x, strike_y);

			// Makes the actual Llightning strike animation appear 
			if (scnt < FCNT) {
				SDL_Rect t{strike_x - ((lightRadius * 1.5) / 2),  strike_y - ((lightRadius * 1.5) / 2), lightRadius*1.5, lightRadius*1.5};
				SDL_RenderCopy(renderer, Lsprite, &lightAnim[scnt++], &t);
				cout << "Lightning running" << endl;
			}
			else
			{
				scnt = 0;
			}
		}
		else {
			// Draws the lightning cloud on the screen
			drawLightningCloud(renderer, 0, 0, mouse_x, mouse_y);
		}

		// Terminate the program if the player is not alive
		if (!playerAlive) {
			movement_timer.stop();
			survival_timer.stop();
			quit = true;
		}
	}

	return true;
}


bool game_state::handle_event(const SDL_Event &event) {
	bool result = false;
	switch(event.type) {
		case SDL_KEYDOWN:
			switch(event.key.keysym.sym) {
				case SDLK_w:
					go_up = true;
					result = true;
					break;
				case SDLK_s:
					go_down = true;
					result = true;
					break;
				case SDLK_a:
					go_left = true;
					result = true;
					break;
				case SDLK_d:
					go_right = true;
					result = true;
					break;
				default: break;
			} break;
		case SDL_KEYUP:
			switch(event.key.keysym.sym) {
				case SDLK_w:
					go_up = false;
					result = true;
					break;
				case SDLK_s:
					go_down = false;
					result = true;
					break;
				case SDLK_a:
					go_left = false;
					result = true;
					break;
				case SDLK_d:
					go_right = false;
					result = true;
					break;
				default: break;
			} break;
		case SDL_MOUSEBUTTONDOWN:
			if (!lightningActive ) {
				SDL_GetMouseState(&strike_x, &strike_y);
				// Set a timer for 2 real-world seconds to set lightningActive to false
				SDL_AddTimer(2000, timerCallback, nullptr);
				lightningActive = true; // Set lightningActive to true when lightning appears
			    // Update the flag to indicate that a circle is already active
				result = true;
			}
			break;
		case SDL_MOUSEMOTION:
			// Update mouse position
			SDL_GetMouseState(&mouse_x, &mouse_y);
			// Draw the lightning cloud at the cursor position if lightning is not active
			if (!lightningActive) {
				//(renderer, 0, 0, mouse_x, mouse_y);
			}
			break;
		default: break;
	}
	return result;
}
