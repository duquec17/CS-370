#include <iostream>

#include <cstdlib>
#include <ctime>

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL2_framerate.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

using namespace std;

const int WIDTH = 1280;
const int HEIGHT = 720;

const int SCNTW = 7;
const int SCNTH = 2;

inline int constrain(int x, int A, int B) {
	return min(max((x),A),B);
}

int main(int argc, char* argv[]) {
	srand(time(nullptr));
	SDL_Window *w = nullptr;
	SDL_Surface *s = nullptr;

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO) < 0) {
		cerr << "SDL_Init() fail... " << SDL_GetError() << endl;
		exit(EXIT_FAILURE);
	}

	FPSmanager fps;
	SDL_initFramerate(&fps);

	w = SDL_CreateWindow("SDL2 SUCCESS!!!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer *rend = SDL_CreateRenderer(w, -1, 0);

	SDL_SetWindowGrab(w, SDL_TRUE);
	SDL_ShowCursor(SDL_DISABLE);

	//sounds
	Mix_Music *music;
	Mix_Chunk *boing;
	Mix_Chunk *hit;
	Mix_Chunk *woosh;

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	music = Mix_LoadMUS("music1.wav");
	boing = Mix_LoadWAV("boing.wav");
	hit = Mix_LoadWAV("hit.wav");
	woosh = Mix_LoadWAV("woosh.wav");

	Mix_VolumeChunk(hit, 40);
	Mix_VolumeChunk(boing, 60);
	Mix_VolumeChunk(woosh, 200);
	Mix_VolumeMusic(160);

	Mix_PlayMusic(music, -1);

	//background
	SDL_Surface *bkgrnd_s = IMG_Load("background.jpg");
	SDL_Texture *background = SDL_CreateTextureFromSurface(rend, bkgrnd_s);


	//create ball
	SDL_Surface *ball_s = SDL_LoadBMP("ball.bmp");
	int BW = ball_s->w;
	int BH = ball_s->h;
	SDL_Texture *ball_t = SDL_CreateTextureFromSurface(rend, ball_s);
	SDL_FreeSurface(ball_s);

	float bx = (WIDTH - BW) / 2;
	float by = (HEIGHT - BH) / 2;
	float vy = 0;
	float vx = 0;

	//create player
	SDL_Surface *stand_s = SDL_LoadBMP("standing.bmp");
	int SW = stand_s->w / SCNTW;
	int SH = stand_s->h;
	SDL_Texture *stand_t = SDL_CreateTextureFromSurface(rend, stand_s);
	SDL_FreeSurface(stand_s);

	SDL_Surface *run_s = SDL_LoadBMP("running.bmp");
	int RW = run_s->w / SCNTW;
	int RH = run_s->h / SCNTH;
	SDL_Texture *run_t = SDL_CreateTextureFromSurface(rend, run_s);
	SDL_FreeSurface(run_s);

	//create source rects
	SDL_Rect stand[SCNTW];
	for(int i = 0, x = 0, y = 0; x < SCNTW; x++) {
		SDL_Rect &s = stand[i++];
		s.w = SW;
		s.h = SH;
		s.x = x * SW;
		s.y = y;
	}

	SDL_Rect run_right[SCNTW];
	SDL_Rect run_left[SCNTW];
	for(int i = 0, x = 0, y = 0; x < SCNTW; x++) {
		SDL_Rect &r = run_right[i++];
		r.w = RW;
		r.h = RH;
		r.x = x * RW;
		r.y = y * RH;
	}
	for(int i = 0, x = 0, y = 1; x < SCNTW; x++) {
		SDL_Rect &l = run_left[i++];
		l.w = RW;
		l.h = RH;
		l.x = x * RW;
		l.y = y * RH;
	}


	//player location data
	float px = (WIDTH - SW) / 2;
	int py = (HEIGHT - 1 - SH);
	float pvx = 1;


	//score
	int score = 0;
	int highscore = 0;
	int frame = 0;


	SDL_Event e;
	bool paused = false;
	bool quit = false;
	while(!quit){
		while(SDL_PollEvent(&e)) {
			switch(e.type){
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_KEYDOWN:
					switch(e.key.keysym.sym) {
						case SDLK_ESCAPE: quit = true; break;
						case SDLK_RETURN:
							paused = !paused;
							if(paused) {
								SDL_ShowCursor(SDL_ENABLE);
								SDL_SetWindowGrab(w, SDL_FALSE);
								Mix_PauseMusic();
							}
							else {
								SDL_ShowCursor(SDL_DISABLE);
								SDL_SetWindowGrab(w, SDL_TRUE);
								Mix_ResumeMusic();
							}
							break;
						case SDLK_SPACE:
							vy -= rand() % 10 + 15;
							vx += rand() % 20 - 10;
							score = 0;
							Mix_PlayChannel(0, woosh, 0);
							break;
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					if(e.button.button = SDL_BUTTON_LEFT) {
						if((by+BH) > py && ((bx+BW) > px && bx < (px+SW))) {
							vx = ((bx+(BW/2))-(px+(SW/2))) * 0.5;
							vy = ((by+(BH/2))-(py+(SH/2))) * 0.5;

							score++;
							if(score > highscore)
								highscore = score;

							Mix_PlayChannel(0, hit, 0);
						}
					}
					break;
				default:
					break;
			}
		}
		if(paused)
			continue;


		int mx,my;
		SDL_GetMouseState(&mx, &my);

		//ball handling
		vy++;
		by += vy;
		bx += vx;

		if(by + BH > HEIGHT - 1) {
			vy = -(vy * 0.7);
			by = HEIGHT - 1 - BH;
			if(fabs(vy) < 3) {
				vx *= 0.9;
			}
			else
				Mix_PlayChannel(1, boing, 0);
			score = 0;
		}

		if(bx + BW > WIDTH - 1) {
			vx = -(vx * 0.7);
			bx = WIDTH - 1 - BW;
			Mix_PlayChannel(1, boing, 0);
		}
		if(bx <= 0) {
			vx = -(vx * 0.7);
			bx = 0;
			Mix_PlayChannel(1, boing, 0);
		}


		//handle player movement
		float offset = (mx-(SW/2)) - px;
		if(abs(offset) > 100) {
			if(offset/abs(offset) == pvx/abs(pvx)) {
				pvx *= 1.1;
			}
			else {
				pvx *= -0.01;
			}
			pvx = constrain(abs((int)round(pvx)), 20, 50) * (offset/abs(offset));
			px += pvx;
		}
		else
			px += (offset * 0.2);


		SDL_Rect ball = {(int)round(bx), (int)round(by), BW, BH};
		SDL_Rect player = {(int)round(px), py, SW, SH};

		//rendering
		SDL_RenderCopy(rend, background, nullptr, nullptr);
		SDL_RenderCopyEx(rend, ball_t, nullptr, &ball, (int)round(bx) * 1.3, nullptr, SDL_FLIP_NONE);
		//player rendering
		if(abs(offset) > 60) {
			if(offset > 0)
				SDL_RenderCopy(rend, run_t, &run_right[frame % SCNTW], &player);
			else
				SDL_RenderCopy(rend, run_t, &run_left[frame % SCNTW], &player);
		}
		else
			SDL_RenderCopy(rend, stand_t, &stand[(int)round(frame/2.5) % SCNTW], &player);


		stringColor(rend, 20, 20, "Click to hit, SPACE to lob, ENTER to pause.", 0xff000000);
		string s = "Best: " + to_string(highscore);
		stringColor(rend, 20, 40, s.c_str(), 0xff000000);
		s = "Score: " + to_string(score);
		stringColor(rend, 20, 50, s.c_str(), 0xff000000);

		SDL_RenderPresent(rend);

		SDL_framerateDelay(&fps);
		frame++;
	}

	Mix_FreeMusic(music);
	Mix_FreeChunk(boing);
	Mix_FreeChunk(hit);
	SDL_DestroyTexture(stand_t);
	SDL_DestroyTexture(run_t);
	SDL_DestroyTexture(ball_t);
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(w);
	SDL_Quit();

	return EXIT_SUCCESS;
}
