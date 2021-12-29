#include "CollisionManager2D.h"
#include "Collider2D.h"

Collider2D::Collider2D()
{
}


Collider2D::~Collider2D()
{

}



bool Collider2D::Collide(Collider2D col)
{
	return false;
}

// ============ BOX COLLIDER ============ 
BoxCollider::BoxCollider()
{
	/*
	if (thistransform != NULL) {
		angle = thistransform->worldrotation;
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
	*/
	width = -1;
	height = -1;
	CollisionManager2D.AddToList(this);

}


bool BoxCollider::Collide(Collider2D* col)
{
	//Box-Circle collision
	if (typeid(*col) == typeid(CircleCollider)) {

	}
	//Box-Box collision
	else if (typeid(*col) == typeid(BoxCollider)) {

	}

	return true;
}


BoxCollider::~BoxCollider()
{

}
// ============ BOX COLLIDER END ============ 

// ============ CIRCLE COLLIDER ============ 
CircleCollider::CircleCollider()
{
	/*
	SpriteRenderer* _sr = this->gameObject->GetComponent<SpriteRenderer>();
	if (_sr != NULL) {
		radius = _sr->GetHalfWidth() + _sr->GetHalfHeight();
	}
	else {
		radius = 50;
	}
	*/
	radius = -1;
	CollisionManager2D.AddToList(this);
}

bool CircleCollider::Collide(Collider2D* col)
{
	//Circle-Circle collision
	if (typeid(*col) == typeid(CircleCollider)) {
		CircleCollider* other = (CircleCollider*)col;
		
		float Dist2 = (radius + other->radius)* (radius + other->radius);

		if ((this->Owner()->transform->worldposition- other->Owner()->transform->worldposition).LengthSquared() <= Dist2 ) {
			cout << "COLLIDED!!!!!\n";
			return true;
		}
		
	}
	//Circle-Box collision
	else if (typeid(*col) == typeid(BoxCollider)) {

	}

	return false;
}
CircleCollider::~CircleCollider()
{

}

// ============ CIRCLE COLLIDER END ============ 

