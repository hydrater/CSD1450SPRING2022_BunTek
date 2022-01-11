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
	SortList();
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

void RenderComponent::SortList(void)
{
	// Sort by layer in ascending order
}
