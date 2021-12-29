#include "Transform.h"
#include "Entity.h"

Transform::Transform() :
	localscale(1, 1),
	localrotation(),
	worldrotation(),
	right(1, 0),
	left(-1, 0),
	up(0, 1),
	down(0, -1),
	parent(NULL)
{
}

Transform::~Transform()
{
}

void Transform::Set(Vector2 position, Vector2 scale, float rotation)
{
	this->worldposition = position;
	this->worldscale = scale;
	this->worldrotation = rotation;
}

void Transform::SetPosition(Vector2 position)
{
	this->worldposition = position;
}

void Transform::SetScale(Vector2 scale)
{
	this->worldscale = scale;
}

void Transform::SetRotation(float rotation)
{
	this->worldrotation = rotation;
}

void Transform::SetRight(Vector2 right)
{
	this->right = right;
}

void Transform::Translate(Vector2 translate)
{
	this->worldposition += translate;
}

void Transform::Rotate(float rotate)
{
	worldrotation = worldrotation + rotate;
}

void Transform::Scale(float scale)
{
	this->worldscale *= scale;
}

const Vector2& Transform::Right()
{
	return right;
}

const Vector2& Transform::Left()
{
	return left;
}

const Vector2& Transform::Up()
{
	return up;
}

const Vector2& Transform::Down()
{
	return down;
}