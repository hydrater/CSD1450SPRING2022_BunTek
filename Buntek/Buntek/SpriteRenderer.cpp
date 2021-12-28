#include "SpriteRenderer.h"
#include "AssetManager.h"

SpriteRenderer::SpriteRenderer()
{
	halfHeight = 100;
	halfWidth = 100;
	texture = 0;
	mesh = 0;
	AssetManager.AddToList(this);
}

SpriteRenderer::~SpriteRenderer()
{
	cout << "sprite renderer deconstructor called" << endl;
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
