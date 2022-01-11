#include "Transform.h"
#include "Entity.h"
#include "Collider2D.h"

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
	worldscale = Vector2(1, 1);
}

Transform::~Transform()
{
}

void Transform::Set(Vector2 position, Vector2 scale, float rotation)
{
	SetPosition(position);
	SetScale(scale);
	SetRotation(rotation);
}

void Transform::SetPosition(Vector2 position)
{
	this->worldposition = position;
	for (size_t i = 0; i < children.size(); ++i)
		children[i]->SetPosition(position);
}

void Transform::SetScale(Vector2 scale)
{
	this->worldscale = scale;
	for (size_t i = 0; i < children.size(); ++i)
		children[i]->SetScale(scale);
}

void Transform::SetRotation(float rotation)
{
	this->worldrotation = rotation;
	for (size_t i = 0; i < children.size(); ++i)
		children[i]->SetRotation(rotation);
}

void Transform::SetRight(Vector2 right)
{
	this->right = right;
	for (size_t i = 0; i < children.size(); ++i)
		children[i]->SetRight(right);
}

void Transform::Translate(Vector2 translate)
{
	this->worldposition += translate;
	for (size_t i = 0; i < children.size(); ++i)
		children[i]->Translate(translate);
}

void Transform::Rotate(float rotate)
{
	this->worldrotation = worldrotation + rotate;

	if (this->Owner()->GetComponent<Collider2D>())
		this->Owner()->GetComponent<Collider2D>()->UpdateDimension();

	for (size_t i = 0; i < children.size(); ++i)
		children[i]->Rotate(rotate);
}

void Transform::Scale(float scale)
{
	this->worldscale *= scale;
	for (size_t i = 0; i < children.size(); ++i)
		children[i]->Scale(scale);
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