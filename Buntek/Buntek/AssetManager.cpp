#include "AssetManager.h"

_assetManager* _assetManager::instance = 0;

_assetManager::_assetManager()
{
    mesh = 0;
    texture = AEGfxTextureLoad("./Resources/Art/Steven.jpg");
    AE_ASSERT_MESG(texture, "Failed to create texture1!!");
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
        AEGfxTextureSet(texture, 0, 0);
        AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
    }
}

void _assetManager::AddToList(SpriteRenderer* spriteRenderer)
{
    rendererList.push_back(spriteRenderer);
}

void _assetManager::Free(void)
{
    // Free and delete
}

void _assetManager::FreeAll(void)
{
    AEGfxMeshFree(mesh);
    AEGfxTextureUnload(texture);
    rendererList.clear();
}
