#pragma once
#include "SpriteRenderer.h"

class Collider2D : public Component
{
public:
	Collider2D(void);
	~Collider2D(void);
	void UpdateDimension(void);
	bool Collide(Collider2D col);
	Transform* transform = 0;

	float width;
	float height;
	float radius;
	float angle; //clockwise rotation

private:

};

class BoxCollider : public Collider2D
{
public:
	BoxCollider(void);
	~BoxCollider(void);
	bool Collide(Collider2D* other);
	

private:
	

};

class CircleCollider : public Collider2D
{
public:
	CircleCollider(void);
	~CircleCollider(void);
	bool Collide(Collider2D* other);
	

private:
	

};
