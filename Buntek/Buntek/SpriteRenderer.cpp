#include "SpriteRenderer.h"
#include "AssetManager.h"

SpriteRenderer::SpriteRenderer(void)
{
	AssetManager.AddToList(this);
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

string SpriteRenderer::GetFontName(void)
{
	return fontString;
}

void SpriteRenderer::SetFont(string fontName)
{
	fontString = fontName;
}
string SpriteRenderer::GetText(void)
{
	return text;
}

void SpriteRenderer::SetText(string _text)
{
	text = _text;
	AEGfxGetPrintSize(AssetManager.GetFont(fontString), &text[0], textScale, TextWidth, TextHeight);
	TextWidth = TextWidth * (float)AEGetWindowWidth()/2;
	TextHeight = TextHeight* (float)AEGetWindowHeight()/2;
	if (TextWidth / 2 > halfWidth) {
		halfWidth = TextWidth / 2 + buffer;
	}
	if (TextHeight / 2 > halfHeight) {
		halfHeight = TextHeight / 2 + buffer;
	}
}
float SpriteRenderer::GetTransparency()
{
	return transparency;
}

void SpriteRenderer::SetTransparency(float value)
{
	transparency = value;
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

void SpriteRenderer::SetColor(float _R, float _G, float _B)
{
	R = _R, G = _G, B = _B;
}
void SpriteRenderer::SetTextColor(float _R, float _G, float _B)
{
	TextR = _R, TextG = _G, TextB = _B;
}
