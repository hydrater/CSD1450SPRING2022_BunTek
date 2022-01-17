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
	if (AEInputCheckTriggered(AEVK_LBUTTON))
	{
		for (BallBehavior* x : ballList)
		{
			x->HitBall(GameManager.GetCursorPosition(), true);
		}
	}
	if (LaunchLine != 0)
	{
		Vector2 temp = GameManager.GetCursorPosition();
		Vector2 tempCalculation = temp;
		float tempAngle = 0;

		temp = (temp - LaunchBall->transform->worldposition);
		LaunchLine->transform->Owner()->GetComponent<SpriteRenderer>()->Size(5,temp.Length());
		tempAngle = Vector2(0, 1).AngleBetween(temp) / 3.1415926535897932384626433832795f * 180.0f;
		if (tempCalculation.x < LaunchBall->transform->worldposition.x)
		{
			tempAngle = -tempAngle;
		}

		LaunchLine->transform->SetRotation(tempAngle);
		temp = temp.Divide(2) + LaunchBall->transform->worldposition;
		LaunchLine->transform->SetPosition(temp);
	}
	if (AEInputCheckTriggered(AEVK_RBUTTON))
	{
		Vector2 tempcursorposition = GameManager.GetCursorPosition();
		if (tempcursorposition.x < GameManager.friendlyAreaX && tempcursorposition.x > GameManager.areaLeftBoundary && tempcursorposition.y 
			< GameManager.areaTopBoundary && tempcursorposition.y > GameManager.areaBottomBoundary)
		{
			CircleCollider* launchcol;
			GameObject* launchBallTrail = new GameObject();
			SpriteRenderer* LaunchTrailRenderer;
			LaunchTrailRenderer = launchBallTrail->AddComponent<SpriteRenderer>();
			LaunchTrailRenderer->Size(20, 20);
			LaunchTrailRenderer->SetTexture("Trail.png");
			LaunchTrailRenderer->SetColor(1, 1, 1);
			LaunchTrailRenderer->SetTransparency(0.75f);
			
			LaunchBall = new GameObject();
			SpriteRenderer* temporaryRenderer;
			temporaryRenderer = LaunchBall->AddComponent<SpriteRenderer>();
			temporaryRenderer->SetLayer(2);
			temporaryRenderer->Size(20, 20);
			temporaryRenderer->SetTexture("ball.png");
			BallBehavior* temporaryBall;
			temporaryBall = LaunchBall->AddComponent<BallBehavior>();
			temporaryBall->AssignListPointer(this);
			temporaryBall->ballTrail = launchBallTrail;
			temporaryBall->srBallTrail = LaunchTrailRenderer;
			temporaryBall->Owner()->transform->SetPosition(tempcursorposition);
			temporaryBall->playerPossess = false;
			temporaryBall->radius = 10;
			temporaryBall->sr = temporaryRenderer;
			temporaryRenderer->SetColor(0, 0, 1);
			launchcol = LaunchBall->AddComponent<CircleCollider>();

			LaunchLine = new GameObject();
			temporaryRenderer = LaunchLine->AddComponent<SpriteRenderer>();
			temporaryRenderer->SetLayer(3);
			temporaryRenderer->SetTexture("WhiteTexture.png");
			temporaryRenderer->Size(0, 0);
		}
	}
	else if (AEInputCheckReleased(AEVK_RBUTTON) && LaunchBall != NULL)
	{
		BallBehavior* LaunchBallCalculator;
		LaunchBallCalculator = LaunchBall->GetComponent<BallBehavior>();
		Vector2 temp = GameManager.GetCursorPosition();
		temp = -(temp - LaunchBallCalculator->Owner()->transform->worldposition);
		if (temp.x < 0)
		{
			temp.x = -temp.x;
		}
		LaunchBallCalculator->SetSpeed(300);
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

	if (targetedBall->playerPossess == isPlayer && acceptableRange)
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

	vecPosition->x = AEClamp(vecPosition->x, GameManager.areaLeftBoundary, GameManager.areaRightBoundary);
	vecPosition->y = AEClamp(vecPosition->y, GameManager.areaBottomBoundary, GameManager.areaTopBoundary);

	Cursor->setcursorposition(*vecPosition);

	Paddle->movePaddle(*vecPosition, isPlayer);
}
