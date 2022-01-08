#include "AssetManager.h"
#include "System.h"
#include <math.h>

_assetManager* _assetManager::instance = 0;

_assetManager::_assetManager()
{
    LoadTexture("Steven.jpg");
    LoadTexture("splash.png");
    LoadTexture("Background.jpg");
    LoadTexture("WhiteTexture.png");
    LoadTexture("BlackTexture.png");
    LoadTexture("ball.png");
    LoadTexture("Trail.png");
    LoadTexture("paddle.png");
    LoadTexture("MainMenu.png");
    LoadTexture("BetterNebula.png");
    LoadTexture("Buttons.png");
    //font

    LoadFont("EquinoxR.otf");
    LoadFont("EquinoxB.otf");
    LoadFont("Metrolic.ttf");

    mesh = 0;

    AEGfxMeshStart();

    AEGfxTriAdd(
        -0.5f, -0.5f, 0x00FF00FF, 0.0f, 1.0f,
        0.5f, -0.5f, 0x00FFFF00, 1.0f, 1.0f,
        -0.5f, 0.5f, 0x0000FFFF, 0.0f, 0.0f);

    AEGfxTriAdd(
        0.5f, -0.5f, 0x00FFFFFF, 1.0f, 1.0f,
        0.5f, 0.5f, 0x00FFFFFF, 1.0f, 0.0f,
        -0.5f, 0.5f, 0x00FFFFFF, 0.0f, 0.0f);

    mesh = AEGfxMeshEnd();
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
        halfWidth *= rendererList[i]->GetTransform()->worldscale.x;
        halfHeight *= rendererList[i]->GetTransform()->worldscale.y;

        Transform* transform = rendererList[i]->GetTransform();

        float rotationAngle = transform->worldrotation;
		Vector2 BottomLeft = Vector2(halfWidth, -halfHeight);
		Vector2 BottomRight = Vector2(-halfWidth, -halfHeight);
		Vector2 TopLeft = Vector2(halfWidth, halfHeight);
		Vector2 TopRight = Vector2(-halfWidth, halfHeight);

        BottomLeft.Rotate(rotationAngle);
        BottomRight.Rotate(rotationAngle);
        TopLeft.Rotate(rotationAngle);
        TopRight.Rotate(rotationAngle);

        AEGfxSetPosition(transform->worldposition.x, transform->worldposition.y);

        // In case matrix is unable to rotate properly
        /*AEGfxMeshStart();

        AEGfxTriAdd(
            BottomLeft.x, BottomLeft.y, 0x00FF00FF, 0.0f, 1.0f,
            BottomRight.x, BottomRight.y, 0x00FFFF00, 1.0f, 1.0f,
            TopLeft.x, TopLeft.y, 0x0000FFFF, 0.0f, 0.0f);

        AEGfxTriAdd(
            BottomRight.x, BottomRight.y, 0x00FFFFFF, 1.0f, 1.0f,
            TopRight.x, TopRight.y, 0x00FFFFFF, 1.0f, 0.0f,
            TopLeft.x, TopLeft.y, 0x00FFFFFF, 0.0f, 0.0f);

        mesh = AEGfxMeshEnd();

        float TransformMatrix[3][3]{
            {halfWidth * 2,0,transform->worldposition.x},
            {0,halfHeight * 2,transform->worldposition.y},
            {0,0,1}
        };*/

        // Scale and Rotate Matrix
        //rotationAngle = 0;
        float cosAngle = cosf(rotationAngle / 180.0f * 3.1415926535897932384626433832795f);
        float sinAngle = sinf(rotationAngle / 180.0f * 3.1415926535897932384626433832795f);
        float width = halfWidth * 2;
        float height = halfHeight * 2;
        // Multiply Matrix by scale according to the GameObject Size then by rotation
        float TransformMatrix[3][3]{
            {cosAngle*width,sinAngle*height,transform->worldposition.x},
            {-sinAngle*width,cosAngle*height,transform->worldposition.y},
            {0,0,1}
        };

        AEGfxSetTransform(TransformMatrix);

        AEGfxSetTintColor(rendererList[i]->R, rendererList[i]->G, rendererList[i]->B, rendererList[i]->GetTransparency());
        //AEGfxSetTextureMode(AE_GFX_TM_PRECISE); Different quality if using average
        AEGfxTextureSet(GetTexture(rendererList[i]->GetTextureName()), 0, 0);
        AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
        //AEGfxMeshFree(mesh);
    }
}

void _assetManager::RenderAllText(void)
{
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);


    for (int i = 0; i < rendererTextList.size(); ++i)
    {
        Transform* transform = rendererTextList[i]->GetTransform();
        //Text Rendering
        AEGfxPrint(GetFont(rendererTextList[i]->GetFontName()), &rendererTextList[i]->GetText()[0],
            (transform->worldposition.x - rendererTextList[i]->TextWidth / 2) / ((float)AEGetWindowWidth() / 2),
            (transform->worldposition.y - rendererTextList[i]->TextHeight / 2) / ((float)AEGetWindowHeight() / 2),
            rendererTextList[i]->textScale, rendererTextList[i]->TextR, rendererTextList[i]->TextG, rendererTextList[i]->TextB);

    }
}

void _assetManager::AddToList(SpriteRenderer* spriteRenderer)
{
    rendererList.push_back(spriteRenderer);
}

void _assetManager::AddToTextList(TextRenderer* textRenderer)
{
    rendererTextList.push_back(textRenderer);
}

void _assetManager::FreeAll(void)
{
    rendererList.clear();
    rendererTextList.clear();
    // memory leak? lol
   /* try {
        if (mesh != 0)
            AEGfxMeshFree(mesh);
        map<string, AEGfxTexture*>::iterator start;
        for (start = textureDatabase.begin(); start != textureDatabase.end(); start++)
            AEGfxTextureUnload(start->second);

        textureDatabase.clear();
    }
    catch (const std::exception) {

    }*/
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
    string pathname = "./Assets/" + name;
    char font = AEGfxCreateFont(&pathname.front(), 48);
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

