#include "AssetManager.h"

_assetManager* _assetManager::instance = 0;

_assetManager::_assetManager()
{
    LoadTexture("Steven.jpg");
    mesh = 0;
}

_assetManager::~_assetManager()
{

}

_assetManager& _assetManager::Instance(void)
{
    if (instance != 0)
    {
        return *instance;
    }
    instance = new _assetManager();
    // Init here

    return *instance;
}

void _assetManager::RenderAll(void)
{
    AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
    AEGfxSetTransparency(1.0f);
    AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);

    for (int i = 0; i < rendererList.size(); ++i)
    {
        if (rendererList[i]->remove)
        {
            delete rendererList[i];
            rendererList.erase(rendererList.begin() + i);
            --i;
            continue;
        }

        float halfWidth = rendererList[i]->GetHalfWidth();
        float halfHeight = rendererList[i]->GetHalfHeight();
        Transform* transform = rendererList[i]->GetTransform();

        AEGfxMeshStart();
        AEGfxTriAdd(
            -halfWidth, -halfHeight, 0x00FF00FF, 0.0f, 1.0f,
            halfWidth, -halfHeight, 0x00FFFF00, 1.0f, 1.0f,
            -halfWidth, halfHeight, 0x0000FFFF, 0.0f, 0.0f);

        AEGfxTriAdd(
            halfWidth, -halfHeight, 0x00FFFFFF, 1.0f, 1.0f,
            halfWidth, halfHeight, 0x00FFFFFF, 1.0f, 0.0f,
            -halfWidth, halfHeight, 0x00FFFFFF, 0.0f, 0.0f);

        mesh = AEGfxMeshEnd();

        AEGfxSetPosition(transform->localposition.x, transform->localposition.y);
        AEGfxTextureSet(GetTexture(rendererList[i]->GetTextureName()) , 0, 0);
        AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
        AEGfxMeshFree(mesh);
    }
}

void _assetManager::AddToList(SpriteRenderer* spriteRenderer)
{
    rendererList.push_back(spriteRenderer);
}

void _assetManager::FreeAll(void)
{
    rendererList.clear();

    if (mesh != 0)
        AEGfxMeshFree(mesh);

    try {
        map<string, AEGfxTexture*>::iterator start;
        for (start = textureDatabase.begin(); start != textureDatabase.end(); start++)
            AEGfxTextureUnload(start->second);

        textureDatabase.clear();
    }
    catch (const std::exception) {
        // Block of code to handle errors
    }
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
    {
        return search->second;
    }
    return NULL;
}

