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

	// PlayerAI Activate
	if (AEInputCheckTriggered(AEVK_O))
	{
		PlayerAIEnabled = !PlayerAIEnabled;
	}
	playerpaddle->setplayerpaddle(!PlayerAIEnabled);
	playerCursor->setplayerpossess(!PlayerAIEnabled);

	if (PlayerAIEnabled || AIEnabled)
		AIscalingTimer += DeltaTime;

	if (PlayerAIEnabled)
	{
		PlayerAITimer -= DeltaTime;
		UpdateAIPosition(playerCursor, playerpaddle, &PlayerAITimer, true);
	}
	else
	{
		playerpaddle->movePaddle(GameManager.GetCursorPosition(), true);
	}

	if (AIEnabled)
	{
		AITimer -= DeltaTime;
		UpdateAIPosition(AICursor, AIPaddle, &AITimer, false);
	}
}

void BattleInput2::RemoveFromList(BallBehavior* ballbehavior)
{
	for (int i = 0; i < ballList.size(); ++i)
	{
		if (ballList[i] == ballbehavior)
		{
			ballList.erase(ballList.begin() + i);
			return;
		}
	}
}

void BattleInput2::UpdateAIPosition(CursorBehaviour* Cursor, PaddleBehavior* Paddle, float* Timer, bool isPlayer)
{
	Vector2* vecPosition = isPlayer ? &PlayerAIposition : &AIposition;
	Vector2* vecTargetPosition = isPlayer ? &PlayerAITargetPosition : &AITargetPosition;

	BallBehavior* targetedBall = ballList[0];

	for (BallBehavior* x : ballList)
	{
		if (x->playerPossess != isPlayer)
			continue;

		if (x->Owner()->transform->worldposition.x > targetedBall->Owner()->transform->worldposition.x && !isPlayer)
			targetedBall = x;
		if (x->Owner()->transform->worldposition.x < targetedBall->Owner()->transform->worldposition.x && isPlayer)
			targetedBall = x;
	}

	Transform* temp = targetedBall->Owner()->transform;

	bool acceptableRange = (temp->worldposition.x >= GameManager.hostileAreaX && !isPlayer) || (temp->worldposition.x <= GameManager.friendlyAreaX && isPlayer);

	if (targetedBall->listCheck == 139 && targetedBall->playerPossess == isPlayer && acceptableRange)
	{
		float estimate = (*vecPosition).operator-(*vecTargetPosition).Length() - targetedBall->velocity.Length();

		vecTargetPosition->x = temp->worldposition.x + (targetedBall->velocity.x * estimate);
		vecTargetPosition->y = temp->worldposition.y + (targetedBall->velocity.y * estimate);
		vecTargetPosition->x = AEClamp(vecTargetPosition->x, GameManager.areaLeftBoundary, GameManager.areaRightBoundary);
		vecTargetPosition->y = AEClamp(vecTargetPosition->y, GameManager.areaBottomBoundary, GameManager.areaTopBoundary);
	}
	else
	{
		*vecTargetPosition = isPlayer ? Vector2(-800, 0) : Vector2(800, 0);
	}

	// Move position towards the targetedPosition
	*vecPosition = (*vecPosition).Lerp(*vecTargetPosition, AIspeed);

	// Calculate Distance to targetedBall
	float dist = (*vecPosition).operator-(temp->worldposition).Length();
	// Hit Ball if within AOE
	if (dist <= GameManager.clickAoERadius)
	{
		targetedBall->HitBall(
			Vector2(temp->worldposition.x + RandFloatMinMax(1, GameManager.clickAoERadius),
				temp->worldposition.y + RandIntMinMax(-1, 1) * RandFloatMinMax(1, GameManager.clickAoERadius / 1.3f)),
			isPlayer);
		if (Timer < 0)
		{
			targetedBall->SetSpeed(targetedBall->GetSpeed() + AIscalingTimer * 3);
			*Timer = RandFloatMinMax(0.7f - AIscalingTimer * 0.005f, 1.5f - AIscalingTimer * 0.005f);
		}
	}

	vecPosition->x = AEClamp(vecPosition->x, GameManager.areaLeftBoundary, GameManager.areaRightBoundary);
	vecPosition->y = AEClamp(vecPosition->y, GameManager.areaBottomBoundary, GameManager.areaTopBoundary);

	Cursor->setcursorposition(*vecPosition);

	Paddle->movePaddle(*vecPosition, isPlayer);
}
