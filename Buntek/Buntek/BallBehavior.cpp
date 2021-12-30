#include "BallBehavior.h"

BallBehavior::BallBehavior()
{
	position.Set(0, 0);
	velocity.Set(1, 1);
	radius = 250;
	clickableAngleLeft = 90;
	clickableAngleRight = 90;
	speed = 6;
	transform = 0;
}

BallBehavior::~BallBehavior()
{

}


void BallBehavior::Test()
{
	
}

void BallBehavior::Start(void)
{
	cout << "Ball created" << endl;
	transform = this->Owner()->transform;
}

void BallBehavior::Update(void)
{
	position.Set(transform->worldposition.x, transform->worldposition.y);

	transform->SetPosition(Vector2(transform->worldposition.x + velocity.x * speed, transform->worldposition.y + velocity.y * speed));

	if (((float)AEGetWindowWidth()/2 - fabs(transform->worldposition.x)) < radius) {
		this->Owner()->Delete();
	}
	else if (((float)AEGetWindowHeight()/2 - fabs(transform->worldposition.y)) < radius) {
		velocity.y = -velocity.y;
	}

}

float BallBehavior::GetSpeed()
{
	return speed;
}

