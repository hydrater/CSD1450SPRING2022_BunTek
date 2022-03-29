/*!*****************************************************************************
\file AssetManager.h
\author: <to be inserted>
\co-authors: Algene Tan Chuan Hong, Isaiah Lim Ji Rong, Steven Koe, Bryan Boh Tai Hong, Goh Kiat Beng
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
    void UnloadTexture(string name);
    void LoadTexture(string name);
    AEGfxTexture* GetTexture(string name);
    char GetFont(string name);
    void AddToList(SpriteRenderer* spriteRenderer);
    void AddToTextList(TextRenderer* textRenderer);
    int GetdefaultFontSize(void);
    void Free(void);
};
