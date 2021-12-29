#pragma once
#include "Collider2D.h"
#include "SpriteRenderer.h"

class CircleCollider : Collider2D
{
public:
	CircleCollider();
	~CircleCollider();
	bool Collide(Collider2D *other);

private:
	Transform* transform;
	float radius;
};