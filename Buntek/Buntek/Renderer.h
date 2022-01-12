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
    static _renderer* instance;
    _renderer();
    ~_renderer();
    AEGfxVertexList* mesh;
    vector<RenderComponent*> rendererList;
    int binarySearch(vector<RenderComponent*> a, int item, int low, int high);
    void insertionSort(void);

public:
    static _renderer& Instance(void);
    void Update(void);
    void AddToList(RenderComponent* entry);
    void FreeAll(void);
};
