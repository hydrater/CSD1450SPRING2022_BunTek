#include "PaddleBehavior.h"
#include "GameManager.h"
#include "SpriteRenderer.h"


PaddleBehavior::PaddleBehavior()
{

}

PaddleBehavior::~PaddleBehavior()
{

}

void PaddleBehavior::Start(void)
{
	transform = this->Owner()->transform;
}

void PaddleBehavior::Update(void)
{
	position = Vector2(transform->worldposition.x, transform->worldposition.y);
}

void PaddleBehavior::movePaddle(Vector2 mousePos, bool isPlayer)
{
	if (isPlayer != playerPaddle) {
		return;
	}
	Transform* tempTransform = Owner()->transform;
	if (transform == nullptr)
		return;

	float xDelta = mousePos.x - tempTransform->worldposition.x, yDelta = mousePos.y - tempTransform->worldposition.y;

	float mag = Vector2(xDelta, yDelta).Length();
	if (mag >= MinMoveDist) {

		speed = GameManager.lerpF(Minspeed, Maxspeed, mag / Maxspeed * (float)AEFrameRateControllerGetFrameTime());

		velocity = Vector2((mousePos.x - tempTransform->worldposition.x), (mousePos.y - tempTransform->worldposition.y)).Normalize();

		transform->SetPosition(Vector2(transform->worldposition.x + velocity.x * speed * (float)AEFrameRateControllerGetFrameTime(), transform->worldposition.y + velocity.y * speed * (float)AEFrameRateControllerGetFrameTime()));

		if (fabs(transform->worldposition.x - GameManager.areaLeftBoundary) <= sr->GetHalfWidth() || fabs(transform->worldposition.x - GameManager.friendlyAreaX) <= sr->GetHalfWidth())
		{
			transform->worldposition.x = AEClamp(transform->worldposition.x, GameManager.areaLeftBoundary + sr->GetHalfWidth(), GameManager.friendlyAreaX - sr->GetHalfWidth());
		}
		if (fabs(transform->worldposition.y - GameManager.areaBottomBoundary) <= sr->GetHalfHeight() || fabs(transform->worldposition.y - GameManager.areaTopBoundary) <= sr->GetHalfHeight())
		{
			transform->worldposition.y = AEClamp(transform->worldposition.y, GameManager.areaBottomBoundary + sr->GetHalfHeight(), GameManager.areaTopBoundary - sr->GetHalfHeight());
		}
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

void PaddleBehavior::setMinspeed(float _Minspeed)
{
	Minspeed = _Minspeed;
}

void PaddleBehavior::setMinMoveDist(float _MinMoveDist)
{
	MinMoveDist = _MinMoveDist;
}