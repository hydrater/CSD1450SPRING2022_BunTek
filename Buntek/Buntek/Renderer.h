/*!*****************************************************************************
\file Renderer.h
\author: <to be inserted>
\co-authors: Algene Tan Chuan Hong, Isaiah Lim Ji Rong, Steven Koe, Bryan Boh Tai Hong, Goh Kiat Beng
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Alpha Engine Renderer
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
