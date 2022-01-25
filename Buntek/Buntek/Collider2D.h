#pragma once
#include "SpriteRenderer.h"

class Collider2D : public Component
{
public:
	Collider2D(void);
	~Collider2D(void);
	//void UpdateDimension(void);
	bool Collide(Collider2D col);
	vector<Vector2> SortMinMax(vector<Vector2> vectors, bool xaxis);
	vector<Vector2> GetRectCorners(Vector2 pos, float width, float height, float angle); // Rotates in counter-clockwise rot (Follows vector2.h Rotate)
	Transform* transform = 0;
	Vector2 scale = Vector2(1, 1);

	float angle = 0; //clockwise rotation

	Vector2 CollisionPoint = Vector2();

private:

};

class BoxCollider : public Collider2D
{
public:
	BoxCollider(void);
	~BoxCollider(void);
	bool Collide(Collider2D* other);

	float width = 0;
	float height = 0;

private:

};

class CircleCollider : public Collider2D
{
public:
	CircleCollider(void);
	~CircleCollider(void);
	bool Collide(Collider2D* other);

	float radius = 0;

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