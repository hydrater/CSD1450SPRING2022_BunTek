/*!*****************************************************************************
\file Transform.h
\project Beyond Aurorean Skies
\author: Algene Tan Chuan Hong (90%)
\co-authors: Isaiah Lim Ji Rong (2.5%), Steven Koe (2.5%), Bryan Boh Tai Hong (2.5%), Goh Kiat Beng (2.5%)
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Handles Transform
All content © 2022 DigiPen Institute of Technology Singapore. All rights reserved.
*******************************************************************************/

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