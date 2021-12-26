#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Component.h"

#include "Vector2.h"

#include <vector>

using std::vector;

#define DEFAULTRIGHT Vector2(1, 0)
// Transform Component
class Transform : public Component
{
	friend class Entity;
	friend class TransformSystem;
public:
	Transform();
	virtual ~Transform();

	void Set(Vector2 position = Vector2(0, 0), Vector2 scale = Vector2(1, 1), float rotation = 0);
	void SetPosition(Vector2 position);
	void SetScale(Vector2 scale);
	void SetRotation(float rotation);
	void SetRight(Vector2 right);

	void Translate(Vector2 translate);
	void Rotate(float rotate);
	// Scale By ( Uniform Scaling )
	void Scale(float scale);

	// Returns a reference to the transform's right that cannot be modified
	const Vector2& Right();
	const Vector2& Left();
	const Vector2& Up();
	const Vector2& Down();

	Vector2 localposition;
	float localrotation;
	Vector2 localscale;
	Vector2 worldposition;
	float worldrotation;
	Vector2 worldscale;

private:

	Vector2 right;
	Vector2 left;
	Vector2 up;
	Vector2 down;

	Transform* parent;
	vector<Transform*> children;
};

#endif