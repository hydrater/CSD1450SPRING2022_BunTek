#include "PaddleBehavior.h"
#include "GameManager.h"
#include "SpriteRenderer.h"
#include "Collider2D.h"


PaddleBehavior::PaddleBehavior()
{

}

PaddleBehavior::~PaddleBehavior()
{

}

void PaddleBehavior::Start(void)
{
	transform = this->Owner()->transform;
	boxcoll->transform = transform;
}

void PaddleBehavior::Update(void)
{
	position = Vector2(transform->worldposition.x, transform->worldposition.y);
}

void PaddleBehavior::movePaddle(Vector2 mousePos, bool isPlayer)
{
	
	Transform* tempTransform = Owner()->transform;
	if (transform == nullptr)
		return;
	if (isPlayer) {
		float xDelta = mousePos.x - tempTransform->worldposition.x, yDelta = mousePos.y - tempTransform->worldposition.y;

		float mag = Vector2(xDelta, yDelta).Length();
		if (mag >= MinMoveDist) {

			speed = GameManager.lerpF(0, Maxspeed, mag / Maxspeed) * (float)AEFrameRateControllerGetFrameTime();

			velocity = Vector2(xDelta / mag, yDelta / mag);

			transform->SetPosition(Vector2(transform->worldposition.x + velocity.x * speed, transform->worldposition.y + velocity.y * speed));


			if (fabs(transform->worldposition.x - GameManager.areaLeftBoundary) <= sr->GetHalfWidth() || fabs(transform->worldposition.x - GameManager.friendlyAreaX) <= sr->GetHalfWidth()
				|| transform->worldposition.x > GameManager.friendlyAreaX || transform->worldposition.x < GameManager.areaLeftBoundary)
			{
				transform->worldposition.x = AEClamp(transform->worldposition.x, GameManager.areaLeftBoundary + sr->GetHalfWidth(), GameManager.friendlyAreaX - sr->GetHalfWidth());
			}
			if (fabs(transform->worldposition.y - GameManager.areaBottomBoundary) <= sr->GetHalfHeight() || fabs(transform->worldposition.y - GameManager.areaTopBoundary) <= sr->GetHalfHeight()
				|| transform->worldposition.y < GameManager.areaTopBoundary || transform->worldposition.y > GameManager.areaBottomBoundary)
			{
				transform->worldposition.y = AEClamp(transform->worldposition.y, GameManager.areaBottomBoundary + sr->GetHalfHeight(), GameManager.areaTopBoundary - sr->GetHalfHeight());
			}
		}
		return;
	}
	else if (!isPlayer) {
		float xDelta = mousePos.x - tempTransform->worldposition.x, yDelta = mousePos.y - tempTransform->worldposition.y;

		float mag = Vector2(xDelta, yDelta).Length();
		if (mag >= MinMoveDist) {

			speed = GameManager.lerpF(0, Maxspeed, mag / Maxspeed) * (float)AEFrameRateControllerGetFrameTime();

			velocity = Vector2(xDelta / mag, yDelta / mag);

			transform->SetPosition(Vector2(transform->worldposition.x + velocity.x * speed, transform->worldposition.y + velocity.y * speed));


			if (fabs(transform->worldposition.x - GameManager.hostileAreaX) <= sr->GetHalfWidth() || fabs(transform->worldposition.x - GameManager.areaRightBoundary) <= sr->GetHalfWidth()
				|| transform->worldposition.x > GameManager.hostileAreaX || transform->worldposition.x < GameManager.areaRightBoundary)
			{
				transform->worldposition.x = AEClamp(transform->worldposition.x, GameManager.hostileAreaX + sr->GetHalfWidth(), GameManager.areaRightBoundary - sr->GetHalfWidth());
			}
			if (fabs(transform->worldposition.y - GameManager.areaBottomBoundary) <= sr->GetHalfHeight() || fabs(transform->worldposition.y - GameManager.areaTopBoundary) <= sr->GetHalfHeight()
				|| transform->worldposition.y < GameManager.areaTopBoundary || transform->worldposition.y > GameManager.areaBottomBoundary)
			{
				transform->worldposition.y = AEClamp(transform->worldposition.y, GameManager.areaBottomBoundary + sr->GetHalfHeight(), GameManager.areaTopBoundary - sr->GetHalfHeight());
			}
		}
		return;
	}
	
}


void PaddleBehavior::setplayerpaddle(bool _playerpaddle) 
{
	playerPaddle = _playerpaddle;
}

void PaddleBehavior::setspeed(float _speed)
{
	speed = _speed;
}

void PaddleBehavior::setMaxspeed(float _Maxspeed)
{
	Maxspeed = _Maxspeed;
}


void PaddleBehavior::setMinMoveDist(float _MinMoveDist)
{
	MinMoveDist = _MinMoveDist;
}