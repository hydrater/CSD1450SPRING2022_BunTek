#include "AssetManager.h"
#include "System.h"
#include <math.h>

_assetManager::_assetManager()
{
    LoadTexture("Steven.jpg");
    LoadTexture("Background.jpg");
    LoadTexture("WhiteTexture.png");
    LoadTexture("ball.png");
    LoadTexture("hdCircle.png");

    // UI
    LoadTexture("UI/Texture.png");
    LoadTexture("UI/Button.png");
    LoadTexture("UI/DialogueBox.png");

    LoadTexture("Stars2.png");
    LoadTexture("Stars3.png");
    LoadTexture("star123.png");
    LoadTexture("Static Stars 1.png");
    LoadTexture("Static Stars 2.png");
    LoadTexture("More Stars 1.png");
    LoadTexture("More Stars 2.png");
    LoadTexture("NebulaBig.png");
    LoadTexture("NebulaCloudBig.png");
    LoadTexture("HoverTexture.png");
    //font
    LoadFont("Ayar.ttf");
    LoadFont("Astral.ttf");
    LoadFont("Gabriola.ttf");
    LoadFont("Metrolic.ttf");
    LoadFont("GothicA1.ttf");

    //Artifacts
    LoadTexture("Artifacts/BouncyNecklace.png");
    LoadTexture("Artifacts/Defiance.png");
    LoadTexture("Artifacts/Dexterity.png");
    LoadTexture("Artifacts/DualStrike.png");
    LoadTexture("Artifacts/FreezingTouch.png");
    LoadTexture("Artifacts/HealingFountain.png");
    LoadTexture("Artifacts/HealthBuddy.png");
    LoadTexture("Artifacts/HealthThief.png");
    LoadTexture("Artifacts/LastStand.png");
    LoadTexture("Artifacts/LethalCut.png");
    LoadTexture("Artifacts/LifeofChampion.png");
    LoadTexture("Artifacts/NinjaShoes.png");
    LoadTexture("Artifacts/Power.png");
    LoadTexture("Artifacts/Reflection.png");
    LoadTexture("Artifacts/Shield.png");
    LoadTexture("Artifacts/Smacker.png");
    LoadTexture("Artifacts/TreeofLife.png");
    LoadTexture("Artifacts/Trickery.png");
    LoadTexture("Artifacts/Urgency.png");
    LoadTexture("Artifacts/VengefulTrickery.png");
    LoadTexture("Artifacts/ZoomerGoggles.png");
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
    textureDatabase.erase(name);
}

void _assetManager::LoadTexture(string name)
{
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
    string pathname = "./Assets/Font/" + name;
    char font = AEGfxCreateFont(&pathname.front(), defaultFontSize);
    FontDatabase[name] = font;
    AE_ASSERT_MESG(font, "Failed to create Font1!!");
}

char _assetManager::GetFont(string name)
{
    auto search = FontDatabase.find(name);
    if (search != FontDatabase.end())
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
}
