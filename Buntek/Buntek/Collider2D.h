#pragma once
#include "SpriteRenderer.h"

class Collider2D : public Component
{
public:
	Collider2D(void);
	~Collider2D(void);
	bool Collide(Collider2D col);
	Transform* transform = 0;

private:

};

class BoxCollider : public Collider2D
{
public:
	BoxCollider(void);
	~BoxCollider(void);
	void UpdateDimension(void);
	bool Collide(Collider2D* other);
	float width;
	float height;
	float angle; //clockwise rotation
	

private:
	

};

class CircleCollider : public Collider2D
{
public:
	CircleCollider(void);
	~CircleCollider(void);
	void UpdateDimension(void);
	bool Collide(Collider2D* other);
	float radius;
	

private:
	

};


class LineCollider : public Collider2D
{
public:
	LineCollider(void);
	~LineCollider(void);
	bool Collide(Collider2D* other);
	Vector2 point1;
	Vector2 point2;


private:


};