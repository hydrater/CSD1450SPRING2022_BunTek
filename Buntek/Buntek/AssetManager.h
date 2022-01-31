#pragma once
#include <AEEngine.h>
#include <vector>
#include <map>
#include "SpriteRenderer.h"
#include "TextRenderer.h"

#define AssetManager _assetManager::Instance()

class _assetManager
{
private:
    _assetManager();
    ~_assetManager();
    vector<SpriteRenderer*> rendererList;
    vector<TextRenderer*> rendererTextList;
    map<string, AEGfxTexture*> textureDatabase;
    map<string, char> FontDatabase;
    void UnloadTexture(string name);
    void LoadTexture(string name);
    void LoadFont(string name);
    int defaultFontSize = 48;

public:
    static _assetManager& Instance(void);
    AEGfxTexture* GetTexture(string name);
    char GetFont(string name);
    void AddToList(SpriteRenderer* spriteRenderer);
    void AddToTextList(TextRenderer* textRenderer);
    int GetdefaultFontSize(void);
    void Free(void);
};
