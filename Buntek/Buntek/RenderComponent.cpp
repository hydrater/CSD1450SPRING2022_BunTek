/*!*****************************************************************************
\file RenderComponent.cpp
\project Beyond Aurorean Skies
\author: Algene Tan Chuan Hong (90%)
\co-authors: Isaiah Lim Ji Rong (2.5%), Steven Koe (2.5%), Bryan Boh Tai Hong (2.5%), Goh Kiat Beng (2.5%)
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Handles Render Component
All content © 2022 DigiPen Institute of Technology Singapore. All rights reserved.
*******************************************************************************/

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
