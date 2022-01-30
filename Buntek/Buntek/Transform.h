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
	friend class GameObject;
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

	Vector2 localposition;
	float localrotation;
	Vector2 localscale;
	Vector2 worldposition;
	float worldrotation;
	Vector2 worldscale;

private:
	Transform* parent;
	vector<Transform*> children;
};

#endif