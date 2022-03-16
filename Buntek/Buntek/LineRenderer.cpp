/*!*****************************************************************************
\file LineRenderer.cpp
\author: <to be inserted>
\co-authors: Algene Tan Chuan Hong, Isaiah Lim Ji Rong, Steven Koe, Bryan Boh Tai Hong, Goh Kiat Beng
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Handles Renderering of lines
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
