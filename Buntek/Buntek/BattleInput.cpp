/*!*****************************************************************************
\file BattleInput.cpp
\author: Goh Kiat Beng (60%)
\co-authors: Algene Tan Chuan Hong (10%), Isaiah Lim Ji Rong (10%), Steven Koe (10%), Bryan Boh Tai Hong (10%)
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Handles Battle's Input
*******************************************************************************/

#include "BattleInput.h"
#include "BallBehavior.h"
#include "Cursor.h"
#include "Vector2.h"
#include <stdlib.h>
#include <algorithm>
#include "System.h"
#include "GameManager.h"

using namespace Math;

BattleInput::BattleInput(void)
{
	AIEnabled = true;
}

BattleInput::~BattleInput(void)
{

}

void BattleInput::Start(void)
{
	AIposition = Vector2(800, 0);
	AICursor->setcursorposition(AIposition);
}

void BattleInput::Update(void)
{
	//timescale update
	playerpaddle->timeScalar = timeScalar;
	AIPaddle->timeScalar = timeScalar;

	if (LaunchLine != 0)
	{
		Vector2 temp = GameManager.GetCursorPosition();
		Vector2 tempCalculation = temp;
		float tempAngle = 0;

		temp = (temp - LaunchBall->transform->worldposition);
		LaunchLine->transform->Owner()->GetComponent<SpriteRenderer>()->Size(5,temp.Length());
		tempAngle = Vector2(0, 1).AngleBetween(temp) / PI * 180.0f;
		if (tempCalculation.x < LaunchBall->transform->worldposition.x)
		{
			tempAngle = -tempAngle;
		}

		LaunchLine->transform->SetRotation(tempAngle);
		temp = temp.Divide(2) + LaunchBall->transform->worldposition;
		LaunchLine->transform->SetPosition(temp);
	}
	
	if (AEInputCheckReleased(AEVK_RBUTTON) && LaunchBall != NULL)
	{
		BallBehavior* LaunchBallCalculator;
		LaunchBallCalculator = LaunchBall->GetComponent<BallBehavior>();
		Vector2 temp = GameManager.GetCursorPosition();
		temp = -(temp - LaunchBallCalculator->Owner()->transform->worldposition);
		if (temp.x < 0)
		{
			temp.x = -temp.x;
		}
		LaunchBallCalculator->SetSpeed(ballSpeed);
		LaunchBallCalculator->velocity = temp.Normalize();
		
		this->ballList.push_back(LaunchBallCalculator);
		LaunchBall = 0;
		LaunchLine->Delete();
		LaunchLine = 0;
	}
	// PlayerAI Activate
	if (AEInputCheckTriggered(AEVK_O))
	{
		PlayerAIEnabled = !PlayerAIEnabled;
	}
	playerpaddle->setplayerpaddle(!PlayerAIEnabled);
	playerCursor->setplayerpossess(!PlayerAIEnabled);

	if (PlayerAIEnabled || AIEnabled)
		AIscalingTimer += DeltaTime * timeScalar;

	if (PlayerAIEnabled)
	{
		PlayerAITimer -= DeltaTime * timeScalar;
		UpdateAIPosition(playerCursor, playerpaddle, &PlayerAITimer, true);
	}
	else
	{
		playerpaddle->movePaddle(GameManager.GetCursorPosition(), true);
	}

	if (AIEnabled)
	{
		AITimer -= DeltaTime * timeScalar;
		UpdateAIPosition(AICursor, AIPaddle, &AITimer, false);
	}
}

void BattleInput::RemoveFromList(BallBehavior* ballbehavior)
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

void BattleInput::UpdateAIPosition(CursorBehaviour* Cursor, PaddleBehavior* Paddle, float* Timer, bool isPlayer)
{
	Vector2* vecPosition = isPlayer ? &PlayerAIposition : &AIposition;
	Vector2* vecTargetPosition = isPlayer ? &PlayerAITargetPosition : &AITargetPosition;

	BallBehavior* targetedBall = nullptr;

	if (ballList.size() > 0)
		targetedBall = ballList[0];

	for (BallBehavior* ball : ballList)
	{
		if (ball->playerPossess != isPlayer)
			continue;

		if ((ball->Owner()->transform->worldposition.y > targetedBall->Owner()->transform->worldposition.y && !isPlayer)
			|| (ball->Owner()->transform->worldposition.y < targetedBall->Owner()->transform->worldposition.y && isPlayer))
			targetedBall = ball;
	}

	if (targetedBall != nullptr)
	{
		Transform* temp = targetedBall->Owner()->transform;

		bool acceptableRange = (temp->worldposition.y >= GameManager.hostileAreaY && !isPlayer) || (temp->worldposition.y <= GameManager.friendlyAreaY && isPlayer);

		if (targetedBall->playerPossess == isPlayer && acceptableRange)
		{
			float estimate = (*vecPosition).operator-(*vecTargetPosition).Length() - targetedBall->velocity.Length();
			float randomXOffset = RandFloatMinMax(-2.f, 2.f); // Random offset to prevent direct reflection down

			vecTargetPosition->x = temp->worldposition.x + (targetedBall->velocity.x * estimate) + randomXOffset;
			vecTargetPosition->y = temp->worldposition.y + (targetedBall->velocity.y * estimate);
			vecTargetPosition->x = AEClamp(vecTargetPosition->x, GameManager.areaLeftBoundary, GameManager.areaRightBoundary);
			vecTargetPosition->y = AEClamp(vecTargetPosition->y, GameManager.areaBottomBoundary, GameManager.areaTopBoundary);
		}
		else
		{
			*vecTargetPosition = isPlayer ? Vector2(0.f, -AIRestYPosition) : Vector2(0.f, AIRestYPosition);
		}
	}
	else
	{
		*vecTargetPosition = isPlayer ? Vector2(0.f, -AIRestYPosition) : Vector2(0.f, AIRestYPosition);
	}

	// Move position towards the targetedPosition
	*vecPosition = (*vecPosition).Lerp(*vecTargetPosition, AIspeed * timeScalar);

	vecPosition->x = AEClamp(vecPosition->x, GameManager.areaLeftBoundary, GameManager.areaRightBoundary);
	vecPosition->y = AEClamp(vecPosition->y, GameManager.areaBottomBoundary, GameManager.areaTopBoundary);

	Cursor->setcursorposition(*vecPosition);

	Paddle->movePaddle(*vecPosition, isPlayer);
}
