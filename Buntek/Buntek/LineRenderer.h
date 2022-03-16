/*!*****************************************************************************
\file LineRenderer.h
\author: <to be inserted>
\co-authors: Algene Tan Chuan Hong, Isaiah Lim Ji Rong, Steven Koe, Bryan Boh Tai Hong, Goh Kiat Beng
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Handles Renderering of lines
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
