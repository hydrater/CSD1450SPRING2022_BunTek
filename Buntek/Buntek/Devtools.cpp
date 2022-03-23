/*!*****************************************************************************
\file Devtools.cpp
\author: <to be inserted>
\co-authors: Algene Tan Chuan Hong, Isaiah Lim Ji Rong, Steven Koe, Bryan Boh Tai Hong, Goh Kiat Beng
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Handles Dev Tools
*******************************************************************************/

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

GameObject* _devTools::CreateArtifactRewardCard(unsigned long ID, Vector2 pos, short layer) {
    
    // Artifact Background
    const float ArtifactUIXSize = 260.f, ArtifactUIYSize = 310.f;
    GameObject* ArtifactUI = CreateSpriteGameObject("WhiteTexture.png", ArtifactUIXSize, ArtifactUIYSize, AE_GFX_BM_BLEND, pos, layer);
    SpriteRenderer* ArtifactBckgrd = ArtifactUI->GetComponent<SpriteRenderer>();

    // Artifact Name
    const float ArtifactNameXSize = 100.f, ArtifactNameYSize = 100.f;
    const float ArtifactNameXOffset = 46.f, ArtifactNameYOffset = 22.f;
    const float ArtifactNameFontSize = 29.f;
    const int ArtifactNameFontLayerOffset = 2;
    const float ArtifactNameFontColorR = 1.f, ArtifactNameFontColorG = 1.f, ArtifactNameFontColorB = 1.f;
    GameObject* ArtifactName = CreateSpriteGameObject("WhiteTexture.png", ArtifactNameXSize, ArtifactNameYSize, AE_GFX_BM_BLEND, Vector2(pos.x + ArtifactNameXOffset, pos.y + ArtifactNameYOffset), layer, 0);
    TextRenderer* NameText = AddTextToSpriteGameObject(ArtifactName, "Gabriola.ttf", ArtifactDatabase.GetName(ID), TextRenderer::xAlignmentTypes::Mid, TextRenderer::yAlignmentTypes::Mid, ArtifactNameFontSize, layer + ArtifactNameFontLayerOffset);
    NameText->SetTextColor(ArtifactNameFontColorR, ArtifactNameFontColorG, ArtifactNameFontColorB);
    ArtifactUI->AddChild(ArtifactName);

    // Artifact Icon
    const float ArtifactIconXSize = 100.f, ArtifactIconYSize = 100.f;
    const float ArtifactIconXOffset = 47.f, ArtifactIconYOffset = 100.f;
    const int ArtifactIconLayerOffset = 2;
    GameObject* ArtifactIcon = CreateSpriteGameObject(ArtifactDatabase.GetSpriteName(ID), ArtifactIconXSize, ArtifactIconYSize, AE_GFX_BM_BLEND, Vector2(pos.x + ArtifactIconXOffset, pos.y + ArtifactIconYOffset), layer + ArtifactIconLayerOffset);
    ArtifactUI->AddChild(ArtifactIcon);

    // Artifact Description
    const float ArtifactDescXSize = 250.f, ArtifactDescYSize = 200.f;
    const float ArtifactDescXOffset = 10.f, ArtifactDescYOffset = -50.f;
    const float ArtifactDescFontSize = 16.f;
    const int ArtifactDescLayerOffset = 2;
    GameObject* ArtifactDesc = CreateSpriteGameObject("WhiteTexture.png", ArtifactDescXSize, ArtifactDescYSize, AE_GFX_BM_BLEND, Vector2(pos.x + ArtifactDescXOffset, pos.y + ArtifactDescYOffset), layer, 0);
    TextRenderer* DescText = AddTextToSpriteGameObject(ArtifactDesc, "Ayar.ttf", ArtifactDatabase.GetDescription(ID), TextRenderer::xAlignmentTypes::Mid, TextRenderer::yAlignmentTypes::Mid, ArtifactDescFontSize, layer + ArtifactDescLayerOffset, true);
    ArtifactUI->AddChild(ArtifactDesc);

    // Set Background, Name and Description color
    switch (ArtifactDatabase.GetRarity(ID))
    {
    case RarityTypes::Uncommon:
        ArtifactBckgrd->SetTexture("Artifacts/Uncommon.png");
        break;
    case RarityTypes::Rare:
        ArtifactBckgrd->SetTexture("Artifacts/Rare.png");
        break;
    case RarityTypes::Unique:
        ArtifactBckgrd->SetTexture("Artifacts/Unique.png");
        break;
    default:
        ArtifactBckgrd->SetTexture("Artifacts/Common.png");
        break;
    }
    return ArtifactUI;
}

GameObject* _devTools::CreatePriceTagGameObject(int price, short blendMode, Vector2 pos, short layer) {
    float PriceTagXSize = 120.f, PriceTagYSize = 50.f;
    float PriceTagColorR = 0.75f, PriceTagColorG = 0.5f, PriceTagColorB = 0.5f;
    GameObject* PriceTag = CreateSpriteGameObject("WhiteTexture.png", PriceTagXSize, PriceTagYSize, blendMode, pos, layer);
    SpriteRenderer* Tagsr = PriceTag->GetComponent<SpriteRenderer>();
    Tagsr->SetColor(PriceTagColorR, PriceTagColorG, PriceTagColorB);

    float PriceTextXSize = 40.f, PriceTextYSize = 50.f;
    float PriceTextXOffset = 10.f;
    int PriceTextLayerOffset = 1;
    GameObject* PriceTextObj = CreateSpriteGameObject("WhiteTexture.png", PriceTextXSize, PriceTextYSize, blendMode, Vector2(pos.x + PriceTextXOffset, pos.y), layer + PriceTextLayerOffset, 0);
    TextRenderer* PriceText = AddTextToSpriteGameObject(PriceTextObj, "Ayar.ttf", to_string(price), TextRenderer::xAlignmentTypes::Left, TextRenderer::yAlignmentTypes::Mid, 26.f, layer + 1);
    PriceTag->AddChild(PriceTextObj);

    float PriceIconXSize = 40.f, PriceIconYSize = 40.f;
    float PriceIconXOffset = -30.f;
    int PriceIconLayerOffset = 1;
    GameObject* PriceIcon = CreateSpriteGameObject("UI/Stardust.png", PriceIconXSize, PriceIconYSize, blendMode, Vector2(pos.x + PriceIconXOffset, pos.y), layer + PriceIconLayerOffset);
    PriceTag->AddChild(PriceIcon);

    return PriceTag;
}

GameObject* _devTools::CreateLineGameObject(Vector2 pos1, Vector2 pos2, float R, float G, float B, float thickness, short layer, float opacity) {
    // Get Angle
    float angle = atan2(pos1.y - pos2.y, pos1.x - pos2.x) * 180.f / PI;
    // Get Length
    float length = sqrtf(powf(pos1.x - pos2.x, 2) + powf(pos1.y - pos2.y, 2));
    // Get Midpoint Value
    Vector2 midpos = Vector2(pos2.x + (pos1.x - pos2.x)/2.f, pos2.y + (pos1.y - pos2.y) / 2.f);
    // "Draw" Line
    GameObject* lineObj = CreateSpriteGameObject("WhiteTexture.png", length, thickness, AE_GFX_BM_BLEND, midpos, layer, opacity);
    lineObj->transform->SetRotation(-angle);
    lineObj->GetComponent<SpriteRenderer>()->SetColor(R, G, B);
    return lineObj;
}

GameObject* _devTools::CreateArtifactObject(Vector2 pos, unsigned long artifact, int count, short layer)
{
    GameObject* ArtifactUI = CreateSpriteGameObject(ArtifactDatabase.GetSpriteName(artifact), 50, 50, AE_GFX_BM_BLEND, pos, layer);

    return ArtifactUI;
}
