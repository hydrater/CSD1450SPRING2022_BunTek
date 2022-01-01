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
	Transform* GetTransform(void);
	string GetTextureName(void);
	void SetTexture(string textureName);
	float GetTransparency();
	void SetTransparency(float value);
	void SetColor(float _R, float _G, float _B);
	float R = 1, G = 1, B = 1;

private:
	string textureString = "Steven.jpg";
	float halfWidth = 100;
	float halfHeight = 100;
	float transparency = 1;
};
