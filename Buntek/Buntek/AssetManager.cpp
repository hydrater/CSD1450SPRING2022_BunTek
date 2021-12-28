#include "AssetManager.h"

_assetManager* _assetManager::instance = 0;

_assetManager::_assetManager()
{
    mesh = 0;
    texture = AEGfxTextureLoad("./Resources/Art/PlanetTexture.png");
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
    for (int i = 0; i < rendererList.size(); ++i)
    {
        // Render
        //rendererList[i]->Render();

        /*AEGfxMeshStart();
        AEGfxTriAdd(
            -halfwidth, -halfheight, 0x00FF00FF, 0.0f, 1.0f,
            halfwidth, -halfheight, 0x00FFFF00, 1.0f, 1.0f,
            -halfwidth, halfheight, 0x0000FFFF, 0.0f, 0.0f);

        AEGfxTriAdd(
            halfwidth, -halfheight, 0x00FFFFFF, 1.0f, 1.0f,
            halfwidth, halfheight, 0x00FFFFFF, 1.0f, 0.0f,
            -halfwidth, halfheight, 0x00FFFFFF, 0.0f, 0.0f);

        mesh = AEGfxMeshEnd();*/

        //AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
        ////Set Transparency, Transparency will work only if the Blend mode is not NONE.
        //AEGfxSetTransparency(1.0f);
        //// Set position for object 3
        //AEGfxSetPosition(this->owner->transform->localposition.x, this->owner->transform->localposition.y);
        //// Add Blue tint
        //AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
        //// Set texture
        //AEGfxTextureSet(texture, 0, 0);
        //// Drawing the mesh (list of triangles)
        //AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
    }
}

void _assetManager::AddToList(SpriteRenderer* spriteRenderer)
{
    rendererList.push_back(spriteRenderer);
}
