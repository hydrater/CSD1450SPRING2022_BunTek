#pragma once
#include "GameScript.h"
#include "Vector2.h"

class Collider2D : public Component
{
public:
	Collider2D();
	~Collider2D();
	void Collide(void);

private:
	Transform *transform;

};