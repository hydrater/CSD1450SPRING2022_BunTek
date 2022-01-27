#include "PaddleBehavior.h"
#include "GameManager.h"
#include "SpriteRenderer.h"
#include "Collider2D.h"
#include "CollisionManager2D.h"
#include "System.h"

PaddleBehavior::PaddleBehavior()
{

}

PaddleBehavior::~PaddleBehavior()
{
	CollisionManager2D.RemoveFromList(this->Owner()->GetComponent<BoxCollider>());
}

void PaddleBehavior::Start(void)
{
	transform = this->Owner()->transform;
	this->Owner()->GetComponent<BoxCollider>()->transform = transform;
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
			speed = MaxSpeed;
		}
		else {
			speed = (mag / MinMoveDist)* MaxSpeed; //(mag)*5;
			mag = mag < MaxSpeed ? mag: MaxSpeed;
		}

		if (mag != 0) {
			velocity = Vector2(xDelta / mag, yDelta / mag);
			transform->SetPosition(Vector2(transform->worldposition.x + velocity.x * speed * DeltaTime, transform->worldposition.y + velocity.y * speed * DeltaTime));
		}
		
		//Clamp paddle within boundary
		
		transform->worldposition.x = AEClamp(transform->worldposition.x, GameManager.areaLeftBoundary + sr->GetHalfWidth(), GameManager.areaRightBoundary - sr->GetHalfWidth());
		transform->worldposition.y = AEClamp(transform->worldposition.y, GameManager.areaBottomBoundary + sr->GetHalfHeight(), GameManager.friendlyAreaY - sr->GetHalfHeight());

		return;
	}
	else if (!isPlayer) {
		float xDelta = mousePos.x - tempTransform->worldposition.x, yDelta = mousePos.y - tempTransform->worldposition.y;

		float mag = Vector2(xDelta, yDelta).Length();

		if (mag >= MinMoveDist) {
			speed = MaxSpeed;
		}
		else {
			speed = (mag / MinMoveDist) * MaxSpeed; //(mag)*5;
			mag = mag < MaxSpeed ? mag : MaxSpeed;
		}

		if (mag != 0) {
			velocity = Vector2(xDelta / mag, yDelta / mag);
			transform->SetPosition(Vector2(transform->worldposition.x + velocity.x * speed * (float)AEFrameRateControllerGetFrameTime(), transform->worldposition.y + velocity.y * speed * (float)AEFrameRateControllerGetFrameTime()));
		}

		//Clamp paddle within boundary
		transform->worldposition.x = AEClamp(transform->worldposition.x, GameManager.areaLeftBoundary + sr->GetHalfWidth(), GameManager.areaRightBoundary - sr->GetHalfWidth());
		transform->worldposition.y = AEClamp(transform->worldposition.y, GameManager.hostileAreaY + sr->GetHalfHeight(), GameManager.areaTopBoundary - sr->GetHalfHeight());

		return;
	}
	
}


void PaddleBehavior::setplayerpaddle(bool _playerpaddle) 
{
	playerPaddle = _playerpaddle;
}

void PaddleBehavior::setspeed(float _speed)
{
	speed = _speed > MaxSpeed ? MaxSpeed : _speed;
	speed = _speed;
}

void PaddleBehavior::setMaxspeed(float _Maxspeed)
{
	MaxSpeed = _Maxspeed;
}


void PaddleBehavior::setMinMoveDist(float _MinMoveDist)
{
	MinMoveDist = _MinMoveDist;
}