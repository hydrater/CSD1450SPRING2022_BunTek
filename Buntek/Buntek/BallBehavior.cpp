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

	if (fabs(transform->worldposition.x - GameManager.AreaLeftBoundary) <= radius || fabs(transform->worldposition.x - GameManager.AreaRightBoundary) <= radius) {
		this->Owner()->Delete();
	}
	else if (fabs(transform->worldposition.y - GameManager.AreaBottomBoundary) <= radius || fabs(transform->worldposition.y - GameManager.AreaTopBoundary) <= radius) {
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

void BallBehavior::HitBall(Vector2 mousePos)
{
	Transform* tempTransform = Owner()->transform;
	float xDelta = mousePos.x - tempTransform->worldposition.x, yDelta = mousePos.y - tempTransform->worldposition.y;

	if (abs(xDelta) <= GameManager.clickAoERadius && abs(yDelta) <= GameManager.clickAoERadius)
	{
		float mag = Vector2(xDelta, yDelta).Length();

		if (mag <= GameManager.clickAoERadius) {

			velocity.Set(Vector2(-(mousePos.x - tempTransform->worldposition.x) / mag, -(mousePos.y - tempTransform->worldposition.y) / mag));
		}
	}
}

