#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "utils.h"
#include "settings.h"
#include <SDL_ttf.h>

void RenderText(const std::string &message, TTF_Font *font,
	SDL_Color color, int fontSize, SDL_Renderer *renderer, float scaleW, float scaleH, int x, int y)
{
	SDL_Surface *surf = TTF_RenderUTF8_Blended(font, message.c_str(), color);
	if (surf == nullptr) {
		TTF_CloseFont(font);
	}
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
	if (texture == nullptr) {
	}

	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = tileSize * scaleW;
	dst.h = tileSize * scaleH;

	SDL_RenderCopy(renderer, texture, NULL, &dst);

	SDL_FreeSurface(surf);
	SDL_DestroyTexture(texture);
}

SDL_Window* CreateWindow()
{
	SDL_Window* window = SDL_CreateWindow("SDL Game", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (window == nullptr) {
		std::cout << SDL_GetError() << std::endl;
		return NULL;
	}

	return window;
}

SDL_Renderer* CreateRenderer(SDL_Window* window)
{
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	if (renderer == nullptr) {
		std::cout << SDL_GetError() << std::endl;
		return NULL;
	}

	return renderer;
}

SDL_Texture* LoadTexture(const std::string &file, SDL_Renderer *ren)
{
	SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
	if (!texture)
	{
		std::cout << IMG_GetError();
	}
	return texture;
}


void RenderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int scale, bool flip, SDL_Rect *clip)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = tileSize * scale;
	dst.h = tileSize * scale;
	SDL_RendererFlip flip_ = SDL_FLIP_NONE;

	if (flip) {
		flip_ = SDL_FLIP_HORIZONTAL;
	}

	SDL_RenderCopyEx(ren, tex, clip, &dst, 0, NULL, flip_);

}



void RenderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int scale, SDL_Rect *clip, int sizeX, int sizeY)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = tileSize * scale * sizeX;
	dst.h = tileSize * scale * sizeY;

	SDL_RenderCopy(ren, tex, clip, &dst);
}

