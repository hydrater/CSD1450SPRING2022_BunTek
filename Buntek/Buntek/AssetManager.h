#pragma once
#include <AEEngine.h>
#include <vector>
#include <map>
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
    map<string, AEGfxTexture*> textureDatabase;
    void LoadTexture(string name);
    AEGfxTexture* GetTexture(string name);

public:
    static _assetManager& Instance(void);
    void AddToList(SpriteRenderer* spriteRenderer);
    void RenderAll(void);
    void FreeAll(void);
};
