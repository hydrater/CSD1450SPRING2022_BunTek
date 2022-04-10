/*!*****************************************************************************
\file SpriteRenderer.h
\project Beyond Aurorean Skies
\author: Algene Tan Chuan Hong (90%)
\co-authors: Isaiah Lim Ji Rong (2.5%), Steven Koe (2.5%), Bryan Boh Tai Hong (2.5%), Goh Kiat Beng (2.5%)
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Handles Renderering of Sprites
All content © 2022 DigiPen Institute of Technology Singapore. All rights reserved.
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
