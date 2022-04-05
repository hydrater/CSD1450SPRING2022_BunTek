/*!*****************************************************************************
\file RenderComponent.cpp
\author: Algene Tan Chuan Hong (90%)
\co-authors: Isaiah Lim Ji Rong (2.5%), Steven Koe (2.5%), Bryan Boh Tai Hong (2.5%), Goh Kiat Beng (2.5%)
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Handles Render Component
*******************************************************************************/

#ifndef RENDERCOMPONENT_H
#define RENDERCOMPONENT_H

#include "Component.h"

enum class RenderType : short
{
	Sprite = 0,
	Font = 1,
	Line = 2
};

class RenderComponent : public Component
{
public:
	RenderComponent();
	~RenderComponent();

	void SetLayer(short _layer);
	short GetLayer(void);
	void SetType(short _type);
	RenderType GetType(void);
private:
	short layer = 0;
	RenderType type = RenderType::Sprite;
};
#endif
