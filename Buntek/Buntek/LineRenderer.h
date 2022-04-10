/*!*****************************************************************************
\file LineRenderer.h
\project Beyond Aurorean Skies
\author: Algene Tan Chuan Hong (80%)
\co-authors: Isaiah Lim Ji Rong (5%), Steven Koe (5%), Bryan Boh Tai Hong (5%), Goh Kiat Beng (5%)
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Handles Renderering of lines
All content © 2022 DigiPen Institute of Technology Singapore. All rights reserved.
*******************************************************************************/
#pragma once
#include "RenderComponent.h"

class LineRenderer : public RenderComponent
{
private:
	LineRenderer(void);
	~LineRenderer(void);

public:
	vector<AEGfxVertexList*> lineList;
	void Add(Vector2 pos, Vector2 pos2);
};
