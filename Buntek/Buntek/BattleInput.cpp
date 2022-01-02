#include "BattleInput.h"
#include "BallBehavior.h"
#include "Vector2.h"
#include <stdlib.h>
#include <algorithm>
#include "System.h"
#include "GameManager.h"
#include "hisMath.h"

using namespace Math;
float AIscalingTimer = 0;

BattleInput::BattleInput()
{
	AIEnabled = true;
}

BattleInput::~BattleInput()
{

}

void BattleInput::Start(void)
{
	
}

void BattleInput::Update(void)
{
	for (int i = 0; i < ballList.size(); ++i)
	{
		if (ballList[i]->listCheck != 139)
		{
			ballList.erase(ballList.begin() + i);
			--i;
			continue;
		}
	}

	if (AEInputCheckTriggered(AEVK_LBUTTON))
	{
		for (BallBehavior* x : ballList)
		{
			x->HitBall(GetWorldPosition(), true);
		}
	}

	if (AIEnabled)
	{
		AITimer -= DeltaTime;
		AIscalingTimer += DeltaTime;

		if (AITimer < 0)
		{
			BallBehavior* targetedBall = ballList[0];

			for (BallBehavior* x : ballList)
			{
				if (x->playerPossess)
					continue;

				if (x->Owner()->transform->worldposition.x > targetedBall->Owner()->transform->worldposition.x)
					targetedBall = x;
			}

			Transform* temp = targetedBall->Owner()->transform;

			if (temp->worldposition.x  >= GameManager.hostileAreaX)
			{
				targetedBall->HitBall(
					Vector2(temp->worldposition.x + RandFloatMinMax(1, GameManager.clickAoERadius),
						temp->worldposition.y + RandFloatMinMax(1, GameManager.clickAoERadius/1.3f)),
					false);
			}
			targetedBall->SetSpeed(targetedBall->GetSpeed() + AIscalingTimer * 0.03f);
			AITimer = RandFloatMinMax(0.7f - AIscalingTimer*0.01f, 1.5f - AIscalingTimer *0.01f);
		}
	}
}

Vector2 BattleInput::GetWorldPosition(void)
{
	AEInputGetCursorPosition(&worldPosition.x, &worldPosition.y);
	return Vector2(worldPosition.x - (float)AEGetWindowWidth() / 2, -(worldPosition.y - (float)AEGetWindowHeight() / 2));
}
