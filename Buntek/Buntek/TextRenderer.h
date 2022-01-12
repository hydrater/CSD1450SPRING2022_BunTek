#pragma once
#include "Transform.h"
#include "RenderComponent.h"
#include "SpriteRenderer.h"

class TextRenderer : public RenderComponent
{
public:
	TextRenderer(void);
	~TextRenderer(void);

	Transform* GetTransform(void);
	string GetFontName(void);
	void SetFont(string textureName);
	void SetScale(float _scale);
	float GetScale(void);
	string GetText(void);
	void SetText(string textureName);
	void SetTextWidth(float _TextWidth);
	void SetTextHeight(float _TextHeight);
	float GetTextWidth(void);
	float GetTextHeight(void);
	void SetBuffer(float _Buffer);
	void SetLineBuffer(float _LineBuffer);
	float GetBuffer(void);
	float GetLineBuffer(void);
	vector<float> GetTextColor(void);
	void SetTextColor(float _R, float _G, float _B);
	void ScaleTexture(SpriteRenderer* sr);
	float TextR = 1, TextG = 1, TextB = 1;

private:
	string fontString = "EquinoxB.otf";
	float textScale = 1;
	string text = "";
	float textWidth = 0;
	float textHeight = 0;
	float buffer = 10;
	float lineBuffer = 10;

};