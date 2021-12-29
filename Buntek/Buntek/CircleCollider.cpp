#include "CircleCollider.h"
#include "BoxCollider.h"

CircleCollider::CircleCollider()
{
	transform = this->gameObject->transform;

	SpriteRenderer* _sr = this->gameObject->GetComponent<SpriteRenderer>();
	if (_sr != NULL) {
		radius = _sr->GetHalfWidth() + _sr->GetHalfHeight();
	}
	else {
		radius = 50;
	}
}

bool CircleCollider::Collide(Collider2D *col)
{
	//Circle-Circle collision
	if (typeid(*col) == typeid(CircleCollider)) {
		CircleCollider* other = (CircleCollider *) col;
		
	}
	//Circle-Box collision
	else if (typeid(*col) == typeid(BoxCollider)) {

	}

	return true;
}

CircleCollider::~CircleCollider()
{

}


