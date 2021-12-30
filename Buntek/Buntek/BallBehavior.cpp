#include "BallBehavior.h"

BallBehavior::BallBehavior()
{
	position.Set(0, 0);
	velocity.Set(1, 0);

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
	this->Owner()->transform->SetPosition(Vector2(this->Owner()->transform->worldposition.x + velocity.x, this->Owner()->transform->worldposition.y + velocity.y));
	//cout << "poo poo pee pee" << endl;
}


