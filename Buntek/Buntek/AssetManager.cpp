/*!*****************************************************************************
\file AssetManager.cpp
\author: <to be inserted>
\co-authors: Algene Tan Chuan Hong, Isaiah Lim Ji Rong, Steven Koe, Bryan Boh Tai Hong, Goh Kiat Beng
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Manage Assets
*******************************************************************************/
#include "AssetManager.h"
#include "System.h"
#include <math.h>

_assetManager::_assetManager()
{
    LoadTexture("WhiteTexture.png");
    LoadTexture("hdCircle.png");

    // UI
    LoadTexture("UI/Button.png");
    LoadTexture("UI/DialogueBox.png");
    LoadTexture("Menu/Button.png");

    LoadTexture("Static Stars 1.png");
    LoadTexture("Static Stars 2.png");
    LoadTexture("More Stars 1.png");
    LoadTexture("More Stars 2.png");
    LoadTexture("NebulaBig.png");
    LoadTexture("NebulaCloudBig.png");
    LoadTexture("Battlescreen.png");
    LoadTexture("Gameover.png");

    //font
    LoadFont("Ayar.ttf");
    LoadFont("Astral.ttf");
    LoadFont("Gabriola.ttf");
    LoadFont("Metrolic.ttf");
    LoadFont("GothicA1.ttf");

    //Artifacts
    LoadTexture("Artifacts/Common.png");
    LoadTexture("Artifacts/Uncommon.png");
    LoadTexture("Artifacts/Rare.png");
    LoadTexture("Artifacts/Unique.png");

    LoadTexture("Artifacts/AntimatterDice.png");
    LoadTexture("Artifacts/BatterUp.png");
    LoadTexture("Artifacts/BonyCaltrops.png");
    LoadTexture("Artifacts/BrokenClock.png");
    LoadTexture("Artifacts/ChickenSoup.png");
    LoadTexture("Artifacts/ChippedDagger.png");
    LoadTexture("Artifacts/CoolSock.png");
    LoadTexture("Artifacts/Duna.png");
    LoadTexture("Artifacts/GalaxialGourd.png");
    LoadTexture("Artifacts/Hilo.png");
    LoadTexture("Artifacts/LeechMedic.png");
    LoadTexture("Artifacts/MiniBlackHole.png");
    LoadTexture("Artifacts/MochaLatte.png");
    LoadTexture("Artifacts/MolecularAssembler.png");
    LoadTexture("Artifacts/NebulousNeedle.png");
    LoadTexture("Artifacts/OnionCandy.png");
    LoadTexture("Artifacts/OrangeJuice.png");
    LoadTexture("Artifacts/PhotonicBanana.png");
    LoadTexture("Artifacts/PlasticFangs.png");
    LoadTexture("Artifacts/StarryTrampoline.png");
    LoadTexture("Artifacts/TitaniumFan.png");
    LoadTexture("Artifacts/UwUGlu.png");
}

_assetManager::~_assetManager()
{
    
}

_assetManager& _assetManager::Instance(void)
{
    static _assetManager instance;
    return instance;
}

void _assetManager::AddToList(SpriteRenderer* spriteRenderer)
{
    rendererList.push_back(spriteRenderer);
}

void _assetManager::AddToTextList(TextRenderer* textRenderer)
{
    rendererTextList.push_back(textRenderer);
}

void _assetManager::UnloadTexture(string name)
{
    if (!textureDatabase.count(name) || textureDatabase.empty())
        return;

    AEGfxTextureUnload(textureDatabase[name]);
    textureDatabase.erase(name);
}

void _assetManager::LoadTexture(string name)
{
    if (textureDatabase.count(name))
        return;

    string pathname = "./Assets/" + name;
    AEGfxTexture* texture = AEGfxTextureLoad(&pathname.front());
    textureDatabase[name] = texture;
    AE_ASSERT_MESG(texture, "Failed to create texture1!!");
}

AEGfxTexture* _assetManager::GetTexture(string name)
{
    auto search = textureDatabase.find(name);
    if (search != textureDatabase.end())
        return search->second;
    return NULL;
}

void _assetManager::LoadFont(string name)
{
    if (fontDatabase.count(name))
        return;

    string pathname = "./Assets/Font/" + name;
    char font = AEGfxCreateFont(&pathname.front(), defaultFontSize);
    fontDatabase[name] = font;
    AE_ASSERT_MESG(font, "Failed to create Font1!!");
}

char _assetManager::GetFont(string name)
{
    auto search = fontDatabase.find(name);
    if (search != fontDatabase.end())
        return search->second;
    return NULL;
}

int _assetManager::GetdefaultFontSize(void) 
{
    return defaultFontSize;
}

void _assetManager::Free(void)
{
    for (map<string, AEGfxTexture*>::iterator it = textureDatabase.begin(); it != textureDatabase.end(); ++it)
    {
        AEGfxTextureUnload(it->second);
    }
    for (map<string, char>::iterator it = fontDatabase.begin(); it != fontDatabase.end(); ++it)
    {
        AEGfxDestroyFont(it->second);
    }
    textureDatabase.clear();
    fontDatabase.clear();
}
