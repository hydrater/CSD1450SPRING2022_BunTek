#pragma once
#include "Component.h"
#include "Transform.h"

class SpriteRenderer : public Component
{
public:
	SpriteRenderer();
	~SpriteRenderer();

	void Size(float width, float height);
	void Render(void);
	void Free(void);

	AEGfxVertexList* mesh;
	AEGfxTexture* texture;
private:
	Transform transform;
};
