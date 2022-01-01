#include "BallBehavior.h"
#include "GameManager.h"


BallBehavior::BallBehavior()
{
	position = Vector2(0, 0);
	velocity= Vector2(0, 0);
	radius = 250;
	clickableAngleLeft = 90;
	clickableAngleRight = 90;
	speed = 6;
	transform = 0;
	AreaTopBoundary = 0;
	AreaBottomBoundary = 0;
	AreaLeftBoundary = 0;
	AreaRightBoundary = 0;
}

BallBehavior::~BallBehavior()
{
	GameManager.CameraShake(2, 5, Vector2(0, 0));
}

void BallBehavior::Start(void)
{
	cout << "Ball created" << endl;
	transform = this->Owner()->transform;
}

void BallBehavior::Update(void)
{
	position = Vector2(transform->worldposition.x, transform->worldposition.y);

	transform->SetPosition(Vector2(transform->worldposition.x + velocity.x * speed, transform->worldposition.y + velocity.y * speed));

	if (fabs(transform->worldposition.x - AreaLeftBoundary) <= radius || fabs(transform->worldposition.x - AreaRightBoundary) <= radius) {
		this->Owner()->Delete();
	}
	else if (fabs(transform->worldposition.y - AreaBottomBoundary) <= radius || fabs(transform->worldposition.y - AreaTopBoundary) <= radius) {
		velocity.y = -velocity.y;
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

