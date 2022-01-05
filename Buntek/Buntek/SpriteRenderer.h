#pragma once
#include "Transform.h"
#include "Component.h"

class SpriteRenderer : public Component
{
public:
	SpriteRenderer(void);
	~SpriteRenderer(void);

	void Size(float width, float height);
	float GetHalfWidth(void);
	float GetHalfHeight(void);
	Transform* GetTransform(void);
	string GetTextureName(void);
	void SetTexture(string textureName);
	string GetFontName(void);
	void SetFont(string textureName);
	string GetText(void);
	void SetText(string textureName);
	float GetTransparency();
	void SetTransparency(float value);
	float GetColor(char color);
	void SetColor(float _R, float _G, float _B);
	void SetTextColor(float _R, float _G, float _B);
	float textScale = 1;
	float R = 1, G = 1, B = 1;
	float TextR = 1, TextG = 1, TextB = 1;
	float TextWidth = 0;
	float TextHeight = 0;

private:
	string textureString = "Steven.jpg";
	string fontString = "Roboto-Regular.ttf";
	string text = "";
	float halfWidth = 100;
	float halfHeight = 100;
	float transparency = 1;
};
