#pragma once
#include <AEEngine.h>
#include "Transform.h"
#include <vector>
#include "SpriteRenderer.h"

#define AssetManager _assetManager::Instance()

class _assetManager
{
private:
    static _assetManager* instance;
    _assetManager();
    ~_assetManager();
    vector<SpriteRenderer*> rendererList;
    AEGfxVertexList* mesh;
    AEGfxTexture* texture;

public:
    static _assetManager& Instance(void);
    void AddToList(SpriteRenderer* spriteRenderer);
    void RenderAll(void);
    void FreeAll(void);
};
