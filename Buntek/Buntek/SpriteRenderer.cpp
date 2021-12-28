#include "SpriteRenderer.h"
#include "AssetManager.h"

//TODO:
// vector2 size, stores half of the width and length

SpriteRenderer::SpriteRenderer()
{
	halfHeight = 100;
	halfWidth = 100;
	texture = 0;
	mesh = 0;
	AssetManager.AddToList(this);
	cout << "Sprite Renderer added" << endl;
}

SpriteRenderer::~SpriteRenderer()
{

}

void SpriteRenderer::Size(float width, float height)
{
	float halfwidth = width / 2, halfheight = height / 2;
}

float SpriteRenderer::GetHalfWidth(void)
{
	return halfWidth;
}

float SpriteRenderer::GetHalfHeight(void)
{
	return halfHeight;
}

Transform SpriteRenderer::GetTransform(void)
{
	return this->transform;
}
