/*!*****************************************************************************
\file SpriteRenderer.h
\author: <to be inserted>
\co-authors: Algene Tan Chuan Hong, Isaiah Lim Ji Rong, Steven Koe, Bryan Boh Tai Hong, Goh Kiat Beng
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Handles Renderering of Sprites
*******************************************************************************/
#pragma once
#include "Transform.h"
#include "RenderComponent.h"

class SpriteRenderer : public RenderComponent
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
	float GetOpacity();
	void SetOpacity(float value);
	short GetBlendMode();
	void SetBlendMode(short value);
	float GetColor(char color);
	void SetColor(float _R, float _G, float _B);
	void SetTextureOffset(Vector2 offset);
	Vector2 GetTextureOffset(void);
	float R = 1, G = 1, B = 1;

private:
	string textureString = "Steven.jpg";
	float halfWidth = 100;
	float halfHeight = 100;
	float transparency = 1;
	short blendMode = AE_GFX_BM_BLEND;
	Vector2 textureOffset;
};
