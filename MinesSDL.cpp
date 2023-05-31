#pragma execution_character_set("utf-8")

#include <iostream>
#include <ctime>
#include "utils.h"
#include "Time.h"
#include <string>
#include "fileManager.h"
#include "Player.h"
#include "BombsField.h"

#pragma region SDL STUFF
SDL_Event e;
SDL_Window* window;
SDL_Renderer* renderer;

#pragma region TEXT RENDERING STUFF
SDL_Color textColor = { 255, 255, 255 };
TTF_Font* font;
#pragma endregion TEXT RENDERING STUFF

#pragma endregion SDL STUFF

#pragma region FRAMES SKIPPER
double skippingFrames = 0;
bool SkipFrames(int framesToSkip)
{
	if (framesToSkip < skippingFrames)
	{
		skippingFrames = 0;
		return true;
	}
	else
	{
		skippingFrames += Time::GetDeltaTime() * 1000;
		return false;
	}
}
#pragma endregion FRAMES SKIPPER

#pragma region SceneManagment
enum Scene
{
	Game, Menu, Records, NameInput
};

Scene currentScene = Scene::NameInput;

bool ShowGameScene();
bool ShowMenuScene();
bool ShowInputNameScene();
bool ShowRecordsScene();

#pragma endregion

#pragma region MENU SCENE STUFF

// Координаты мыши
int mx, my;
GameObject* menuImage, * tutorialImage, * tutorialButton;
bool tutorialIsActive = false;

#pragma endregion MENU SCENE STUFF


FileWithRecords* records = new FileWithRecords();;

string playerName = "_";
Player* player;
BombField* bombField;



void ResetGame(bool fullReset = true)
{
	player->xPos = 0;
	player->yPos = 0;
	bombField->GenerateNewField();
	bombField->wasShown = false;
	if (fullReset)
		player->levelsCompletedInRow = 0;
}

bool Update()
{
	Time::SetNow(SDL_GetPerformanceCounter());
	SDL_RenderClear(renderer);
	
	if (currentScene == Scene::NameInput && !ShowInputNameScene())
		return false;
	else if (currentScene == Scene::Menu && !ShowMenuScene())
		return false;
	else if (currentScene == Scene::Records && !ShowRecordsScene())
		return false;
	else if (currentScene == Scene::Game && !ShowGameScene())
		return false;
	
	SDL_RenderPresent(renderer);
	Time::Calculate();
	return true;
}

int main(int argc, char** argv)
{
	srand(time(0));
	TTF_Init();
	window = CreateWindow();
	renderer = CreateRenderer(window);
	font = TTF_OpenFont("./progressPixel.ttf", 40);

	bombField = new BombField();
	player = new Player(0, 0);

	menuImage = new GameObject(5, 5, "Sprites/menu.png");
	tutorialImage = new GameObject(5, 5, "Sprites/tutorial.png");
	tutorialButton = new GameObject(0, 6 * 2 + 5, "Sprites/button.png");

	while (Update());

	return 0;
}

bool ShowGameScene()
{
	// При проигрыше (касании игрока бомбы)
	if (bombField->CheckCollision(player))
	{
		player->StopMoving();
		string gameOverText = "Game over";
		RenderText(gameOverText, font, textColor, 28, renderer, gameOverText.length() / 1.5, 2,
			SCREEN_WIDTH / 2 - gameOverText.length() * 8,
			SCREEN_HEIGHT - SCREEN_HEIGHT / 3);

		bombField->Render();


		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_KEYDOWN)
			{
				records->SetNewRecord(player->levelsCompletedInRow, playerName);
				ResetGame();
				currentScene = Scene::Menu;
			}
			if (e.type == SDL_QUIT)
				return false;
		}
	}
	else
	{
		// При выигрыше
		if (player->CheckIfPlayerIsInsideFinish())
		{
			player->StopMoving();
			string youWinText = "You win";
			RenderText(youWinText, font, textColor, 28, renderer, youWinText.length() / 1.5, 2,
				SCREEN_WIDTH / 2 - youWinText.length() * 8,
				SCREEN_HEIGHT - SCREEN_HEIGHT / 3);
			while (SDL_PollEvent(&e))
			{
				
				if (e.type == SDL_KEYDOWN)
				{
					ResetGame(false);
					player->levelsCompletedInRow++;
				}
				if (e.type == SDL_QUIT)
					return false;
			}
		}
		else
		{
			while (SDL_PollEvent(&e))
			{
				if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
						currentScene = Scene::Menu;
				player->GetMoveDirectionFromInput(e);
			}
			if (e.type == SDL_QUIT)
				return false;
		}

	}

	player->Move();


	player->Render();

	if (!bombField->wasShown)
	{
		// Фаза показа бомб
		if (SkipFrames(1000))
		{
			bombField->wasShown = true;
		}
		player->StopMoving();
		bombField->Render();
	}
	return true;
}

bool ShowRecordsScene()
{
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_KEYDOWN)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_ESCAPE:
			{
				currentScene = Scene::Menu;
				break;
			}
			}
		}
		if (e.type == SDL_QUIT)
			return false;
	}

	string recordString;

	for (int i = 0; i < 10; i++)
	{
		recordString = std::to_string(i + 1) + ": " + records->GetRecordString(i);
		RenderText(recordString, font, textColor, 10, renderer, recordString.length() / 1.5, 2,
			20,
			(i * 2 + 1) * tileSize + tileSize / 2.2);
	}

	return true;
}


bool ShowMenuScene()
{
	SDL_GetMouseState(&mx, &my);

	while (SDL_PollEvent(&e))
	{

		if (e.type == SDL_KEYDOWN)
		{

			switch (e.key.keysym.sym)
			{
			case SDLK_SPACE:
			{
				currentScene = Scene::Game;
				break;
			}
			case SDLK_r:
			{
				currentScene = Scene::Records;
				break;
			}
			case SDLK_ESCAPE:
			{
				return false;
				break;
			}
			}
		}
		if (e.type == SDL_QUIT)
			return false;
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			if (mx > tutorialButton->xPos && mx < tutorialButton->xPos + tileSize * 2
				&& my > tutorialButton->yPos && my < tutorialButton->yPos + tileSize * 2 && !tutorialIsActive)
				tutorialIsActive = true;
			else
				tutorialIsActive = false;

		}
	}

	menuImage->Render(15);
	if (tutorialIsActive)
		tutorialImage->Render(15);

	tutorialButton->Render(2);

	return true;
}



bool ShowInputNameScene()
{
	RenderText("Верещагин М.А О715Б", font, textColor, 20, renderer, 12, 1.6, 30, 30);

	RenderText("Input your name: (length < 10)", font, textColor, 20, renderer, 12, 1.6,
		SCREEN_WIDTH / 2 - 17 * 10,
		SCREEN_HEIGHT / 4);
	RenderText(playerName, font, textColor, 20, renderer, playerName.length() / 1.3, 1.8,
		SCREEN_WIDTH / 2 - playerName.length() * 12,
		SCREEN_HEIGHT / 2);

	string navText = "SPACE - continue";

	RenderText(navText, font, textColor, 20, renderer, navText.size() / 1.2, 2,
		SCREEN_WIDTH / 2 - navText.size() * 12,
		SCREEN_HEIGHT - SCREEN_HEIGHT / 4);

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_KEYDOWN)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_BACKSPACE:
			{
				playerName = "_";
				break;
			}
			case SDLK_SPACE:
			{
				if (playerName.size() < 10)
				{
					if (playerName == "_")
						playerName = "Default";
					currentScene = Menu;
				}
				else
					playerName = "_";
				break;
			}
			}
		}
		else if (e.type == SDL_TEXTINPUT)
		{
			if (playerName == "_")
				playerName = "";
			playerName += e.text.text;
		}
		if (e.type == SDL_QUIT)
			return false;
	}
	return true;
}