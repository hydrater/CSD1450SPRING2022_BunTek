#include "PlayerInput.h"
#include "BallBehavior.h"
#include "Vector2.h"
#include <stdlib.h>
#include <algorithm>

PlayerInput::PlayerInput()
{

}

PlayerInput::~PlayerInput()
{

}

void PlayerInput::Start(void)
{
	
}

void PlayerInput::Update(void)
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

			ballList[i]->HitBall(GetWorldPosition(), true);
		}
	}
}

Vector2 PlayerInput::GetWorldPosition(void)
{
	AEInputGetCursorPosition(&worldPosition.x, &worldPosition.y);
	return Vector2(worldPosition.x - (float)AEGetWindowWidth() / 2, -(worldPosition.y - (float)AEGetWindowHeight() / 2));
}
