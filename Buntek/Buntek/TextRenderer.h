#pragma once
#include "Transform.h"
#include "Component.h"
#include "SpriteRenderer.h"

class TextRenderer : public Component
{
public:
	TextRenderer(void);
	~TextRenderer(void);

	Transform* GetTransform(void);
	string GetFontName(void);
	void SetFont(string textureName);
	string GetText(void);
	void SetText(string textureName);
	vector<float> GetTextColor(void);
	void SetTextColor(float _R, float _G, float _B);
	void ScaleTexture(SpriteRenderer* sr);
	float textScale = 1;
	float TextR = 1, TextG = 1, TextB = 1;
	float TextWidth = 0;
	float TextHeight = 0;
	float buffer = 10;

private:
	string fontString = "EquinoxB.otf";
	string text = "";

};