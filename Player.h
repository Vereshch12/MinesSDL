#pragma once
#include "GameObject.h"
#include "Time.h"
#include <string>

extern SDL_Color textColor;
extern TTF_Font* font;

class Player : public GameObject
{
private:
	int m_Speed = 10;
	int lastMoveDirectionX = 0, lastMoveDirectionY = 0;
public:
	int levelsCompletedInRow = 0;

	Player(int xPos, int yPos) : GameObject(xPos, yPos, "Sprites/player.png") { }

	void GetMoveDirectionFromInput(SDL_Event& e)
	{
		if (e.type == SDL_KEYDOWN)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_a: lastMoveDirectionX = -1; return;
			case SDLK_d: lastMoveDirectionX = 1; return;
			case SDLK_w: lastMoveDirectionY = 1; return;
			case SDLK_s: lastMoveDirectionY = -1; return;
			}
		}
		else if (e.type == SDL_KEYUP)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_a: case SDLK_d: lastMoveDirectionX = 0; return;
			case SDLK_w: case SDLK_s: lastMoveDirectionY = 0; return;
			}
		}
	}

	void StopMoving()
	{
		lastMoveDirectionX = 0;
		lastMoveDirectionY = 0;
	}

	void Move()
	{
		if (xPos > SCREEN_WIDTH - tileSize)
			xPos = SCREEN_WIDTH - tileSize;
		else if (xPos < 0)
			xPos = 0;
		else
			xPos += m_Speed * Time::GetDeltaTime() * 30 * lastMoveDirectionX;

		if (yPos > SCREEN_HEIGHT - tileSize)
			yPos = SCREEN_HEIGHT - tileSize;
		else if (yPos < 0)
			yPos = 0;
		else
			yPos -= m_Speed * Time::GetDeltaTime() * 30 * lastMoveDirectionY;
	}

	inline bool CheckIfPlayerIsInsideFinish()
	{
		return yPos < SCREEN_HEIGHT - tileSize && yPos > SCREEN_HEIGHT - tileSize * 2;
	}

	void Render(int sizeInc_ = 1) override
	{
		// Point text
		std::string pointsText = std::to_string(levelsCompletedInRow);
		RenderText(pointsText, font, textColor, 28, renderer, pointsText.length() / 1.8, 1.1, 20, 60);

		GameObject::Render();
	}
};