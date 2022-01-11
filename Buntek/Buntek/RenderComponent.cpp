#include "RenderComponent.h"

RenderComponent::RenderComponent()
{
}

RenderComponent::~RenderComponent()
{
}

void RenderComponent::SetLayer(short _layer)
{
	layer = _layer;
}

short RenderComponent::GetLayer(void)
{
	return layer;
}
