#ifndef utils
#define utils

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>




SDL_Window* CreateWindow();
SDL_Renderer* CreateRenderer(SDL_Window* window);
SDL_Texture* LoadTexture(const std::string &file, SDL_Renderer *ren);
void RenderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int scale = 1, SDL_Rect *clip = nullptr, int sizeX = 1, int sizeY = 1);
void RenderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int scale, bool flip, SDL_Rect *clip = nullptr);
void RenderText(const std::string &message, TTF_Font *font,
	SDL_Color color, int fontSize, SDL_Renderer *renderer, float scaleW, float scaleH, int x, int y);
#endif // !utils

