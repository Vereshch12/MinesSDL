#pragma once
#include <SDL.h>
#include "utils.h"
#include "settings.h"

extern SDL_Renderer* renderer;

class GameObject
{
protected:
	SDL_Texture* texture;
public:
	float xPos = 0;
	float yPos = 0;
	GameObject() = default;

	GameObject(int xPos, int yPos, std::string texturePath)
	{
		this->xPos = xPos * tileSize;
		this->yPos = yPos * tileSize;
		texture = LoadTexture(texturePath, renderer);
	}

	virtual void Render(int sizeInc_ = 1)
	{
		RenderTexture(texture, renderer, xPos, yPos, sizeInc_);
	}
	virtual void Render(int xSize, int ySize, int sizeInc_ = 1)
	{
		RenderTexture(texture, renderer, xPos, yPos, sizeInc_, nullptr, xSize, ySize);
	}

	void RenderFlipped(int sizeInc_ = 1)
	{
		RenderTexture(texture, renderer, xPos, yPos, sizeInc_, true, nullptr);
	}
};