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
    temp->AddComponent<SpriteRenderer>()->SetOpacity(1);
    SpriteRenderer* tempRenderer = temp->GetComponent<SpriteRenderer>();
    tempRenderer->SetLayer(0);
    tempRenderer->SetTexture(spriteName);
    tempRenderer->Size(xSize, ySize);
    tempRenderer->SetBlendMode((AEGfxBlendMode)blendMode);
    temp->transform->SetPosition(pos);
    tempRenderer->SetOpacity(1.0f);
    return temp;
}

GameObject* _devTools::CreateSpriteGameObject(string spriteName, float xSize, float ySize, short blendMode, Vector2 pos, short layer) {
    GameObject* temp = new GameObject();
    temp->AddComponent<SpriteRenderer>()->SetOpacity(1);
    SpriteRenderer* tempRenderer = temp->GetComponent<SpriteRenderer>();
    tempRenderer->SetLayer(layer);
    tempRenderer->SetTexture(spriteName);
    tempRenderer->Size(xSize, ySize);
    tempRenderer->SetBlendMode((AEGfxBlendMode)blendMode);
    temp->transform->SetPosition(pos);
    tempRenderer->SetOpacity(1.0f);
    return temp;
}

GameObject* _devTools::CreateSpriteGameObject(string spriteName, float xSize, float ySize, short blendMode, Vector2 pos, short layer, float opacity) {
    GameObject* temp = new GameObject();
    temp->AddComponent<SpriteRenderer>()->SetOpacity(1);
    SpriteRenderer* tempRenderer = temp->GetComponent<SpriteRenderer>();
    tempRenderer->SetLayer(layer);
    tempRenderer->SetTexture(spriteName);
    tempRenderer->Size(xSize, ySize);
    tempRenderer->SetBlendMode((AEGfxBlendMode)blendMode);
    temp->transform->SetPosition(pos);
    tempRenderer->SetOpacity(opacity);
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

GameObject* _devTools::CreateArtifactUIGameObject(unsigned long ID, Vector2 pos, short layer) {
    
    // Artifact Background
    GameObject* ArtifactUI = CreateSpriteGameObject("WhiteTexture.png", 290, 300, AE_GFX_BM_BLEND, pos, layer - 1);
    SpriteRenderer* ArtifactBckgrd = ArtifactUI->GetComponent<SpriteRenderer>();
    // Artifact Name
    GameObject* ArtifactName = CreateSpriteGameObject("WhiteTexture.png", 200.f, 100.f, AE_GFX_BM_BLEND, Vector2(pos.x, pos.y + 130.f), layer, 0);
    TextRenderer* NameText = AddTextToSpriteGameObject(ArtifactName, "Gabriola.ttf", ArtifactDatabase.GetName(ID), TextRenderer::xAlignmentTypes::Mid, TextRenderer::yAlignmentTypes::Mid, 36.f, layer);
    ArtifactUI->AddChild(ArtifactName);
    // Artifact Icon
    GameObject* ArtifactIcon = CreateSpriteGameObject(ArtifactDatabase.GetSpriteName(ID), 100.f, 100.f, AE_GFX_BM_BLEND, Vector2(pos.x, pos.y + 50.f), layer + 1);
    ArtifactUI->AddChild(ArtifactIcon);
    // Artifact Description
    GameObject* ArtifactDesc = CreateSpriteGameObject("WhiteTexture.png", 290.f, 180.f, AE_GFX_BM_BLEND, Vector2(pos.x, pos.y - 20), layer, 0);
    TextRenderer* DescText = AddTextToSpriteGameObject(ArtifactDesc, "Ayar.ttf", ArtifactDatabase.GetDescription(ID), TextRenderer::xAlignmentTypes::Mid, TextRenderer::yAlignmentTypes::Mid, 20.f, layer, true);
    ArtifactUI->AddChild(ArtifactDesc);
    // Set Background, Name and Description color
    switch (ArtifactDatabase.GetRarity(ID))
    {
    case RarityTypes::Uncommon:
        ArtifactBckgrd->SetColor(0, 0.67f, 0.3f);
        NameText->SetTextColor(0, 0, 0);
        DescText->SetTextColor(0, 0, 0);
        break;
    case RarityTypes::Rare:
        ArtifactBckgrd->SetColor(0, 0.35f, 0.67f);
        NameText->SetTextColor(1, 1, 1);
        DescText->SetTextColor(1, 1, 1);
        break;
    case RarityTypes::Unique:
        ArtifactBckgrd->SetColor(0.92f, 0.57f, 0.31f);
        NameText->SetTextColor(1, 1, 1);
        DescText->SetTextColor(1, 1, 1);
        break;
    default:
        ArtifactBckgrd->SetColor(0.7f, 0.7f, 0.7f);
        NameText->SetTextColor(0, 0, 0);
        DescText->SetTextColor(0, 0, 0);
        break;
    }
    return ArtifactUI;
}

GameObject* _devTools::CreatePriceTagGameObject(int price, short blendMode, Vector2 pos, short layer) {
    GameObject* PriceTag = CreateSpriteGameObject("WhiteTexture.png", 120, 50, blendMode, pos, layer);
    SpriteRenderer* Tagsr = PriceTag->GetComponent<SpriteRenderer>();
    Tagsr->SetColor(0.75f, 0.5f, 0.5f);
    GameObject* PriceTextObj = CreateSpriteGameObject("WhiteTexture.png", 40, 50, blendMode, Vector2(pos.x + 10, pos.y), layer + 1, 0);
    TextRenderer* PriceText = AddTextToSpriteGameObject(PriceTextObj, "Ayar.ttf", to_string(price), TextRenderer::xAlignmentTypes::Left, TextRenderer::yAlignmentTypes::Mid, 26.f, layer + 1);
    PriceTag->AddChild(PriceTextObj);
    GameObject* PriceIcon = CreateSpriteGameObject("Steven.jpg", 40, 40, blendMode, Vector2(pos.x - 30, pos.y), layer + 1);
    PriceTag->AddChild(PriceIcon);
    return PriceTag;
}