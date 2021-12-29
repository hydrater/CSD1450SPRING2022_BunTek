#pragma once
#include "SpriteRenderer.h"


class Collider2D : public Component
{
public:
	Collider2D();
	~Collider2D();
	bool Collide(Collider2D col);

private:

};

class BoxCollider : public Collider2D
{
public:
	BoxCollider();
	~BoxCollider();
	bool Collide(Collider2D* other);
	float width;
	float height;
	float angle; //clockwise rotation
	

private:
	

};

class CircleCollider : public Collider2D
{
public:
	CircleCollider();
	~CircleCollider();
	bool Collide(Collider2D* other);
	float radius;
	

private:
	

};
