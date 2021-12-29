#pragma once
#include "Collider2D.h"
#include "SpriteRenderer.h"

class BoxCollider : Collider2D
{
public:
	BoxCollider();
	~BoxCollider();
	bool Collide(Collider2D *other);

private:
	Transform* transform;
	float width;
	float height;
	float angle; //clockwise rotation
};