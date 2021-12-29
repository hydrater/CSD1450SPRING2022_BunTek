#include "BoxCollider.h"
#include "CircleCollider.h"

BoxCollider::BoxCollider()
{
	transform = this->gameObject->transform;
	if (transform != NULL) {
		angle = transform->worldrotation;
	}
	else {
		angle = 0.0f;
	}

	SpriteRenderer* _sr = this->gameObject->GetComponent<SpriteRenderer>();
	if (_sr != NULL) {
		width = _sr->GetHalfWidth() * 2;
		height = _sr->GetHalfHeight() * 2;
	}
	else {
		width = 100;
		height = 100;
	}
}

bool BoxCollider::Collide(Collider2D *col)
{
	//Circle-Circle collision
	if (typeid(*col) == typeid(CircleCollider)) {

	}
	//Circle-Box collision
	else if (typeid(*col) == typeid(BoxCollider)) {

	}

	return true;
}


BoxCollider::~BoxCollider()
{

}
