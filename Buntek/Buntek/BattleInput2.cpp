#include "BattleInput2.h"
#include "BallBehavior.h"
#include "Cursor.h"
#include "Vector2.h"
#include <stdlib.h>
#include <algorithm>
#include "System.h"
#include "GameManager.h"

using namespace Math;

BattleInput2::BattleInput2(void)
{
	AIEnabled = true;
}

BattleInput2::~BattleInput2(void)
{

}

void BattleInput2::Start(void)
{
	AIposition = Vector2(800, 0);
	AICursor->setcursorposition(AIposition);
}

void BattleInput2::Update(void)
{
	playerpaddle->movePaddle(GameManager.GetCursorPosition(), true);

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
			x->HitBall(GameManager.GetCursorPosition(), true);
		}
	}

	if (AIEnabled)
	{
		AITimer -= DeltaTime;
		AIscalingTimer += DeltaTime;

		BallBehavior* targetedBall = ballList[0];

		for (BallBehavior* x : ballList)
		{
			if (x->playerPossess)
				continue;

			if (x->Owner()->transform->worldposition.x > targetedBall->Owner()->transform->worldposition.x)
				targetedBall = x;
		}

		Transform* temp = targetedBall->Owner()->transform;

		if (temp->worldposition.x >= GameManager.hostileAreaX && targetedBall->listCheck == 139 && !targetedBall->playerPossess)
		{
			float estimate = AIposition.operator-(AITargetPosition).Length() - targetedBall->velocity.Length();

			AITargetPosition.x = temp->worldposition.x + (targetedBall->velocity.x * estimate);
			AITargetPosition.y = temp->worldposition.y + (targetedBall->velocity.y * estimate);
			AITargetPosition.x = AEClamp(AITargetPosition.x, GameManager.areaLeftBoundary, GameManager.areaRightBoundary);
			AITargetPosition.y = AEClamp(AITargetPosition.y, GameManager.areaBottomBoundary, GameManager.areaTopBoundary);
		}
		else
		{
			AITargetPosition = Vector2(800, 0);
		}

		// Move position towards the targetedPosition
		AIposition = AIposition.Lerp(AITargetPosition, AIspeed);

		// Calculate Distance to targetedBall
		float dist = AIposition.operator-(temp->worldposition).Length();
		// Hit Ball if within AOE
		if (dist <= GameManager.clickAoERadius)
		{
			targetedBall->HitBall(
				Vector2(temp->worldposition.x + RandFloatMinMax(1, GameManager.clickAoERadius),
					temp->worldposition.y + RandIntMinMax(-1,1) * RandFloatMinMax(1, GameManager.clickAoERadius / 1.3f)),
				false);
			if (AITimer < 0)
			{
				//targetedBall->SetSpeed(targetedBall->GetSpeed() + AIscalingTimer * 3);
				AITimer = RandFloatMinMax(0.7f - AIscalingTimer * 0.005f, 1.5f - AIscalingTimer * 0.005f);
			}
		}

		AIposition.x = AEClamp(AIposition.x, GameManager.areaLeftBoundary, GameManager.areaRightBoundary);
		AIposition.y = AEClamp(AIposition.y, GameManager.areaBottomBoundary, GameManager.areaTopBoundary);

		AICursor->setcursorposition(AIposition);

		AIPaddle->movePaddle(AIposition, false);
	}
}
