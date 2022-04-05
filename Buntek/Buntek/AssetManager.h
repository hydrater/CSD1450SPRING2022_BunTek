/*!*****************************************************************************
\file AssetManager.h
\author: Algene Tan Chuan Hong (90%)
\co-authors: Isaiah Lim Ji Rong (2.5%), Steven Koe (2.5%), Bryan Boh Tai Hong (2.5%), Goh Kiat Beng (2.5%)
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Manage Assets
*******************************************************************************/
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
    map<string, char> fontDatabase;

    void LoadFont(string name);
    int defaultFontSize = 48;

public:
    static _assetManager& Instance(void);
    void LoadBaseLibrary(void);
    bool baseLoaded = false;
    void UnloadTexture(string name);
    void LoadTexture(string name);
    AEGfxTexture* GetTexture(string name);
    char GetFont(string name);
    void AddToList(SpriteRenderer* spriteRenderer);
    void AddToTextList(TextRenderer* textRenderer);
    int GetdefaultFontSize(void);
    void Free(void);
};
