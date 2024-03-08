#include "DrawText.h"

DrawText::DrawText(TTF_Font* textFont) {
	mTextFont = textFont;
}

void DrawText::Draw(int centerX, int centerY, SDL_Renderer* renderer, const char Text[], SDL_Color textColor) {
	if (mSurfaceMessage) { SDL_FreeSurface(mSurfaceMessage); }
	if (mTextureMessage) { SDL_DestroyTexture(mTextureMessage); }

	mSurfaceMessage = TTF_RenderText_Solid(mTextFont, Text, textColor);

	int textWidth = mSurfaceMessage->w;
	int textHeight = mSurfaceMessage->h;

	SDL_Rect textRect(centerX - textWidth /2, centerY - textHeight / 2, textWidth,textHeight);

	mTextureMessage = SDL_CreateTextureFromSurface(renderer, mSurfaceMessage);

	SDL_RenderCopy(renderer, mTextureMessage, NULL, &textRect);
}