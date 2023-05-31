#include "CollisionUtils.h"

bool CheckCollision(GameObject* obj1, int sizeInc1, GameObject* obj2, int sizeInc2)
{
	int x1 = obj1->xPos, y1 = obj1->yPos;
	int x2 = obj2->xPos, y2 = obj2->yPos;
	int size1 = sizeInc1 * tileSize;
	int size2 = sizeInc2 * tileSize;

	if (y1 < y2)
	{
		if (x1 < x2)
			return (x2 < x1 + size1) && (y2 < y1 + size1);
		else
			return (x1 < x2 + size2) && (y2 < y1 + size1);
	}
	else
	{
		if (x1 < x2)
			return (x2 < x1 + size1) && (y1 < y2 + size2);
		else
			return (x1 < x2 + size2) && (y1 < y2 + size2);
	}
}