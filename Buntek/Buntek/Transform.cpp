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
	this->localposition = position;
	this->localscale = scale;
	this->localrotation = rotation;
}

void Transform::SetPosition(Vector2 position)
{
	this->localposition = position;
}

void Transform::SetScale(Vector2 scale)
{
	this->localscale = scale;
}

void Transform::SetRotation(float rotation)
{
	this->localrotation = rotation;
}

void Transform::SetRight(Vector2 right)
{
	this->right = right;
}

void Transform::Translate(Vector2 translate)
{
	this->localposition += translate;
}

void Transform::Rotate(float rotate)
{
	localrotation = localrotation + rotate;
}

void Transform::Scale(float scale)
{
	this->localscale *= scale;
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