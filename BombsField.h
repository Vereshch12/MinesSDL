#pragma once
#include "GameObject.h"
#include "Bomb.h"
#include "Player.h"
#include <vector>

class BombField
{
private:
	int m_NumOfBombs;
	std::vector<Bomb*> bombs;

public:
	bool wasShown = false; 

	BombField(int numOfBombs = 20) : m_NumOfBombs(numOfBombs)
	{
		GenerateNewField(numOfBombs);
	}

	void GenerateNewField(int numOfBombs = 20)
	{
		ClearField();
		for (size_t i = 0; i < numOfBombs; i++)
			bombs.push_back(new Bomb(rand() % tilesInRow, rand() % (tilesInRow - 4) + 2));
	}

	inline void ClearField()
	{
		bombs.clear();
	}

	bool CheckCollision(GameObject* gameObject)
	{
		for (auto bomb : bombs)
			if (bomb->CheckCollisionWithObject(gameObject))
				return true;
		return false;
	}

	void Render()
	{
		for (auto bomb : bombs)
			bomb->Render();
	}
};