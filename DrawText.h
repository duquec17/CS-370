#ifndef __DRAWTEXT_H__
#define __DRAWTEXT_H__

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class DrawText {
public:
	DrawText(SDL_Rect textRect, SDL_Color textColor, TTF_Font* textFont);

	void Draw(int centerX, int centerY, SDL_Renderer* renderer, const char Text[], SDL_Color textColor);

private:
	SDL_Rect mTextRect;
	SDL_Color mTextColor;
	TTF_Font* mTextFont;
	SDL_Surface* mSurfaceMessage;
	SDL_Texture* mTextureMessage;

};

#endif  /* __DRAWTEXT_H__ */