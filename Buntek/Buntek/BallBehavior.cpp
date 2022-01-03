#include "BallBehavior.h"
#include "GameManager.h"
#include "SpriteRenderer.h"

BallBehavior::BallBehavior(void)
{
}

BallBehavior::~BallBehavior(void)
{
	GameManager.CameraShake(0.5, 50, Vector2(0, 0));
}

void BallBehavior::Start(void)
{
	transform = this->Owner()->transform;
}

void BallBehavior::Update(void)
{
	transform->SetPosition(Vector2(transform->worldposition.x + velocity.x * speed * (float)AEFrameRateControllerGetFrameTime(), transform->worldposition.y + velocity.y * speed * (float)AEFrameRateControllerGetFrameTime()));

	if (fabs(transform->worldposition.x - GameManager.areaLeftBoundary) <= radius || fabs(transform->worldposition.x - GameManager.areaRightBoundary) <= radius) {
		this->Owner()->Delete();
	}
	else if (fabs(transform->worldposition.y - GameManager.areaBottomBoundary) <= radius || fabs(transform->worldposition.y - GameManager.areaTopBoundary) <= radius) 
	{
		velocity.y = -velocity.y;
		transform->worldposition.y = AEClamp(transform->worldposition.y, GameManager.areaBottomBoundary + 5, GameManager.areaTopBoundary - 5);
	}
}

float BallBehavior::GetSpeed(void)
{
	return speed;
}

void BallBehavior::SetSpeed(float _speed)
{
	speed = _speed;
}

void BallBehavior::HitBall(Vector2 mousePos, bool isPlayer)
{
	if (isPlayer != playerPossess)
		return;

	Transform* tempTransform = Owner()->transform;
	if (transform == nullptr)
		return;

	if ((isPlayer && transform->worldposition.x > GameManager.friendlyAreaX) ||
		(!isPlayer && transform->worldposition.x < GameManager.hostileAreaX))
		return;

	float xDelta = mousePos.x - tempTransform->worldposition.x, yDelta = mousePos.y - tempTransform->worldposition.y;

	// Update the delta to prevent almost direct vertical velocity (commented out cuz of weird speed)
	//yDelta = AEClamp(yDelta, GameManager.clickAoERadius * -0.9f, GameManager.clickAoERadius * 0.9f);

	if (abs(xDelta) <= GameManager.clickAoERadius && abs(yDelta) <= GameManager.clickAoERadius)
	{
		float mag = Vector2(xDelta, yDelta).Length();

		if (mag <= GameManager.clickAoERadius) {
			velocity = (Vector2(-(mousePos.x - tempTransform->worldposition.x) / mag, -(mousePos.y - tempTransform->worldposition.y) / mag));

			// Change direction if click is in opposite direction
			if (playerPossess && mousePos.x > tempTransform->worldposition.x || !playerPossess && mousePos.x < tempTransform->worldposition.x)
				velocity.x *= -1;

			playerPossess = !playerPossess;
			playerPossess ? sr->SetColor(1, 0, 0) : sr->SetColor(0, 0, 1);
		}
	}
}

