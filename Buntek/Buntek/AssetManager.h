#pragma once
#include <vector>
#include "SpriteRenderer.h"
#include <AEEngine.h>

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
    //void FreeRenderer() Use vector.erase
};
