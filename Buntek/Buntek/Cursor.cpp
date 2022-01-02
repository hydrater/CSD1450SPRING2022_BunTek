#include "Cursor.h"
#include "BallBehavior.h"
#include "Vector2.h"
#include <stdlib.h>
#include <algorithm>

Cursor::Cursor()
{

}

Cursor::~Cursor()
{

}

void Cursor::Start(void)
{
	
}

void Cursor::Update(void)
{
	if (AEInputCheckTriggered(AEVK_LBUTTON))
	{
		for (int i = 0; i < ballList.size(); ++i)
		{
			if (ballList[i]->listCheck != 0)
			{
				ballList.erase(ballList.begin() + i);
				--i;
				continue;
			}

			ballList[i]->HitBall(GetWorldPosition());
		}
	}
}

Vector2 Cursor::GetWorldPosition(void)
{
	AEInputGetCursorPosition(&worldPosition.x, &worldPosition.y);
	return Vector2(worldPosition.x - (float)AEGetWindowWidth() / 2, -(worldPosition.y - (float)AEGetWindowHeight() / 2));
}
