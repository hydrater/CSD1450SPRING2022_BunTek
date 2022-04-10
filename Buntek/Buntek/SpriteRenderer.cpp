/*!*****************************************************************************
\file SpriteRenderer.cpp
\project Beyond Aurorean Skies
\author: Algene Tan Chuan Hong (90%)
\co-authors: Isaiah Lim Ji Rong (2.5%), Steven Koe (2.5%), Bryan Boh Tai Hong (2.5%), Goh Kiat Beng (2.5%)
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Handles Renderering of Sprites
All content © 2022 DigiPen Institute of Technology Singapore. All rights reserved.
*******************************************************************************/

#include "SpriteRenderer.h"
#include "AssetManager.h"
#include "Collider2D.h"
#include "Renderer.h"

SpriteRenderer::SpriteRenderer(void)
{
	SetType(0);
	Renderer.AddToList(this);
}

SpriteRenderer::~SpriteRenderer(void)
{
	
}

void SpriteRenderer::Size(float width, float height)
{
	halfWidth = width / 2;
	halfHeight = height / 2;
}

float SpriteRenderer::GetHalfWidth(void)
{
	return halfWidth;
}

float SpriteRenderer::GetHalfHeight(void)
{
	return halfHeight;
}

Transform* SpriteRenderer::GetTransform(void)
{
	return this->Owner()->transform;
}

string SpriteRenderer::GetTextureName(void)
{
	return textureString;
}

void SpriteRenderer::SetTexture(string textureName)
{
	textureString = textureName;
}

float SpriteRenderer::GetOpacity()
{
	return transparency;
}

void SpriteRenderer::SetOpacity(float value)
{
	transparency = value;
}

short SpriteRenderer::GetBlendMode()
{
	return blendMode;
}

void SpriteRenderer::SetBlendMode(short value)
{
	blendMode = value;
}

float SpriteRenderer::GetColor(char color)
{
	switch (color)
	{
		case ('R'): return R; break;
		case ('G'): return G; break;
		case ('B'): return B; break;
		default: return 0; break;
	}
}

void SpriteRenderer::SetColor(float _R, float _G, float _B){
	R = _R, G = _G, B = _B;
}

void SpriteRenderer::SetTextureOffset(Vector2 offset)
{
	textureOffset = offset;
}

Vector2 SpriteRenderer::GetTextureOffset(void)
{
	return textureOffset;
}
