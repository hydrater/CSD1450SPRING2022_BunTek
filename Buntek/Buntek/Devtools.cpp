#include "Devtools.h"

_devTools::_devTools()
{

}

_devTools::~_devTools()
{

}

_devTools& _devTools::Instance(void)
{
    static _devTools instance;
    return instance;
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

TextRenderer* _devTools::AddTextToSpriteGameObject(GameObject* gameObject, string fontName, string text, TextRenderer::xAlignmentTypes xAlignment, TextRenderer::yAlignmentTypes yAlignment, float fontsize) {
    TextRenderer* tempTextRenderer;
    tempTextRenderer = gameObject->AddComponent<TextRenderer>();
    tempTextRenderer->SetFont(fontName);
    tempTextRenderer->SetText(text);
    tempTextRenderer->SetXAlignment(xAlignment);
    tempTextRenderer->SetYAlignment(yAlignment);
    tempTextRenderer->SetFontSize(fontsize);
    return tempTextRenderer;
}

TextRenderer* _devTools::AddTextToSpriteGameObject(GameObject* gameObject, string fontName, string text, TextRenderer::xAlignmentTypes xAlignment, TextRenderer::yAlignmentTypes yAlignment, float fontsize, short layer) {
    TextRenderer* tempTextRenderer;
    tempTextRenderer = gameObject->AddComponent<TextRenderer>();
    tempTextRenderer->SetFont(fontName);
    tempTextRenderer->SetText(text);
    tempTextRenderer->SetXAlignment(xAlignment);
    tempTextRenderer->SetYAlignment(yAlignment);
    tempTextRenderer->SetFontSize(fontsize);
    tempTextRenderer->SetLayer(layer);
    return tempTextRenderer;
}

TextRenderer* _devTools::AddTextToSpriteGameObject(GameObject* gameObject, string fontName, string text, TextRenderer::xAlignmentTypes xAlignment, TextRenderer::yAlignmentTypes yAlignment, float fontsize, short layer, bool warparound) {
    TextRenderer* tempTextRenderer;
    tempTextRenderer = gameObject->AddComponent<TextRenderer>();
    tempTextRenderer->SetFont(fontName);
    tempTextRenderer->SetText(text);
    tempTextRenderer->SetXAlignment(xAlignment);
    tempTextRenderer->SetYAlignment(yAlignment);
    tempTextRenderer->SetFontSize(fontsize);
    tempTextRenderer->SetLayer(layer);
    tempTextRenderer->SetWarpAround(warparound);
    return tempTextRenderer;
}