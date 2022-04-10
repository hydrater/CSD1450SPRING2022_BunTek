/*!*****************************************************************************
\file LineRenderer.cpp
\project Beyond Aurorean Skies
\author: Algene Tan Chuan Hong (80%)
\co-authors: Isaiah Lim Ji Rong (5%), Steven Koe (5%), Bryan Boh Tai Hong (5%), Goh Kiat Beng (5%)
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Handles Renderering of lines
All content © 2022 DigiPen Institute of Technology Singapore. All rights reserved.
*******************************************************************************/

#include "LineRenderer.h"
#include "Renderer.h"

LineRenderer::LineRenderer(void)
{
	SetType(2);
	Renderer.AddToList(this);
}

LineRenderer::~LineRenderer(void)
{

}

void LineRenderer::Add(Vector2 pos, Vector2 pos2)
{
    AEGfxVertexList* newLine;
    AEGfxMeshStart();
    AEGfxVertexAdd(pos.x, pos.y, 0xFFFFFFFF, 0.0f, 0.0f);
    AEGfxVertexAdd(pos2.x, pos2.y, 0xFFFFFFFF, 0.0f, 0.0f);
    newLine = AEGfxMeshEnd();

    lineList.push_back(newLine);
}
