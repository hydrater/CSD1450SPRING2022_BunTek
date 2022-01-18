#include "Devtools.h"

_devTools* _devTools::instance = 0;

_devTools::_devTools()
{

}

_devTools::~_devTools()
{

}

_devTools& _devTools::Instance(void)
{
    if (instance != 0)
    {
        return *instance;
    }
    instance = new _devTools();
    return *instance;
}

GameObject* _devTools::CreateSpriteGameObject(string spriteName, float xSize, float ySize, short blendMode, Vector2 pos) {
    GameObject* temp = new GameObject();
    temp->AddComponent<SpriteRenderer>()->SetTransparency(1);
    SpriteRenderer* tempRenderer = temp->GetComponent<SpriteRenderer>();
    tempRenderer->SetLayer(0);
    tempRenderer->SetTexture(spriteName);
    tempRenderer->Size(xSize, ySize);
    tempRenderer->SetBlendMode((AEGfxBlendMode)blendMode);
    temp->transform->SetPosition(pos);
    tempRenderer->SetTransparency(1.0f);
    return temp;
}

GameObject* _devTools::CreateSpriteGameObject(string spriteName, float xSize, float ySize, short blendMode, Vector2 pos, short layer) {
    GameObject* temp = new GameObject();
    temp->AddComponent<SpriteRenderer>()->SetTransparency(1);
    SpriteRenderer* tempRenderer = temp->GetComponent<SpriteRenderer>();
    tempRenderer->SetLayer(layer);
    tempRenderer->SetTexture(spriteName);
    tempRenderer->Size(xSize, ySize);
    tempRenderer->SetBlendMode((AEGfxBlendMode)blendMode);
    temp->transform->SetPosition(pos);
    tempRenderer->SetTransparency(1.0f);
    return temp;
}

GameObject* _devTools::CreateSpriteGameObject(string spriteName, float xSize, float ySize, short blendMode, Vector2 pos, short layer, float opacity) {
    GameObject* temp = new GameObject();
    temp->AddComponent<SpriteRenderer>()->SetTransparency(1);
    SpriteRenderer* tempRenderer = temp->GetComponent<SpriteRenderer>();
    tempRenderer->SetLayer(layer);
    tempRenderer->SetTexture(spriteName);
    tempRenderer->Size(xSize, ySize);
    tempRenderer->SetBlendMode((AEGfxBlendMode)blendMode);
    temp->transform->SetPosition(pos);
    tempRenderer->SetTransparency(opacity);
    return temp;
}