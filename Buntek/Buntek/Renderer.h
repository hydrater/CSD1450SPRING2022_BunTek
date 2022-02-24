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
