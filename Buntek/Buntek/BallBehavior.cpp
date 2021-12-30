#include "BallBehavior.h"

BallBehavior::BallBehavior()
{
	position.Set(0, 0);
	velocity.Set(1, 1);
	radius = 250;
	clickableAngleLeft = 90;
	clickableAngleRight = 90;
}


BallBehavior::~BallBehavior()
{

}


void BallBehavior::Test()
{
	
}

void BallBehavior::Start(void)
{
	cout << "monkaS" << endl;
}

void BallBehavior::Update(void)
{
	position.Set(this->Owner()->transform->worldposition.x, this->Owner()->transform->worldposition.y);

	this->Owner()->transform->SetPosition(Vector2(this->Owner()->transform->worldposition.x + velocity.x, this->Owner()->transform->worldposition.y + velocity.y));

	if (((float)AEGetWindowWidth()/2 - fabs(this->Owner()->transform->worldposition.x)) < radius) {
		//this->Owner()->Delete();
	}
	else if (((float)AEGetWindowHeight()/2 - fabs(this->Owner()->transform->worldposition.y)) < radius) {
		velocity.y = -velocity.y;
	}

	//cout << "poo poo pee pee" << endl;
}


