#include "RenderComponent.h"
#include "Renderer.h"

RenderComponent::RenderComponent()
{
}

RenderComponent::~RenderComponent()
{
}

void RenderComponent::SetLayer(short _layer)
{
	layer = _layer;
	Renderer.InsertionSort();
}

short RenderComponent::GetLayer(void)
{
	return layer;
}

void RenderComponent::SetType(short _type)
{
	type = (RenderType)_type;
}

RenderType RenderComponent::GetType(void)
{
	return type;
}
