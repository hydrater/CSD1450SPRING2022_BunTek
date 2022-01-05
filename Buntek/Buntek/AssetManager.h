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
    map<string, char> FontDatabase;
    void LoadTexture(string name);
    void LoadFont(string name);


public:
    static _assetManager& Instance(void);
    AEGfxTexture* GetTexture(string name);
    char GetFont(string name);
    void AddToList(SpriteRenderer* spriteRenderer);
    void RenderAll(void);
    void FreeAll(void);
};
