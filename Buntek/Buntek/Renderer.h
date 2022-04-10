/*!*****************************************************************************
\file Renderer.h
\project Beyond Aurorean Skies
\author: Algene Tan Chuan Hong (90%)
\co-authors: Isaiah Lim Ji Rong (2.5%), Steven Koe (2.5%), Bryan Boh Tai Hong (2.5%), Goh Kiat Beng (2.5%)
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Alpha Engine Renderer
All content © 2022 DigiPen Institute of Technology Singapore. All rights reserved.
*******************************************************************************/
#pragma once
#include <AEEngine.h>
#include <vector>
#include <map>
#include "AssetManager.h"
#include "RenderComponent.h"

#define Renderer _renderer::Instance()

class _renderer
{
private:
    _renderer();
    ~_renderer();
    AEGfxVertexList* mesh;
    vector<RenderComponent*> rendererList;
    int binarySearch(vector<RenderComponent*> a, int item, int low, int high);

public:
    static _renderer& Instance(void);
    void Update(void);
    void AddToList(RenderComponent* entry);
    float TextAlignmentX(TextRenderer* textRenderer, int lineNum);
    float TextAlignmentY(TextRenderer* textRenderer);
    void WrapAround(TextRenderer* textRenderer);
    void InsertionSort(void);
    void Clear(void);
    void FreeMesh(void);
};
