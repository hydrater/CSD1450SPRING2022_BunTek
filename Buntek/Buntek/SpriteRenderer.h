#pragma once
#include "Component.h"
#include "Transform.h"

class SpriteRenderer : public Component
{
public:
	SpriteRenderer();
	~SpriteRenderer();

	void Size(float width, float height);
	float GetHalfWidth(void);
	float GetHalfHeight(void);
	Transform GetTransform(void);

	AEGfxVertexList* mesh;
	AEGfxTexture* texture;

private:
	float halfWidth;
	float halfHeight;
	Transform transform;
};
