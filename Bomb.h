#pragma once
#include "GameObject.h"
#include "CollisionUtils.h"

class Bomb : public GameObject
{
public: 
	Bomb(int xPos, int yPos) : GameObject(xPos, yPos, "Sprites/bomb.png") { }

	inline bool CheckCollisionWithObject(GameObject* gameObject) { return CheckCollision(this, 1, gameObject, 1); }

};