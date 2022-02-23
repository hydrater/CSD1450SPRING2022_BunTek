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

GameObject* _devTools::CreateArtifactUIGameObject(Artifact artifact, float xSize, float ySize, short blendMode, Vector2 pos, short layer) {
    
    // Artifact Background
    GameObject* ArtifactUI = CreateSpriteGameObject("WhiteTexture.png", xSize, ySize, blendMode, pos, layer - 1);
    SpriteRenderer* ArtifactBckgrd = ArtifactUI->GetComponent<SpriteRenderer>();
    // Artifact Name
    GameObject* ArtifactName = CreateSpriteGameObject("WhiteTexture.png", xSize / 1.5f, ySize / 4.f, blendMode, Vector2(pos.x, pos.y + (ySize / 3.f)), layer, 0);
    TextRenderer* NameText = AddTextToSpriteGameObject(ArtifactName, "Gabriola.ttf", ArtifactDatabase.GetName(artifact.ID), TextRenderer::xAlignmentTypes::Mid, TextRenderer::yAlignmentTypes::Mid, 36.f, layer);
    ArtifactUI->AddChild(ArtifactName);
    // Artifact Icon
    GameObject* ArtifactIcon = CreateSpriteGameObject(ArtifactDatabase.GetSpriteName(artifact.ID), xSize / 2.f, xSize / 2.f, blendMode, pos, layer + 1);
    ArtifactUI->AddChild(ArtifactIcon);
    // Artifact Description
    GameObject* ArtifactDesc = CreateSpriteGameObject("WhiteTexture.png", xSize / 1.5f, ySize / 4.f, blendMode, Vector2(pos.x, pos.y - (ySize / 3.f)), layer, 0);
    TextRenderer* DescText = AddTextToSpriteGameObject(ArtifactDesc, "Gabriola.ttf", ArtifactDatabase.GetDescription(artifact.ID), TextRenderer::xAlignmentTypes::Mid, TextRenderer::yAlignmentTypes::Mid, 36.f, layer);
    ArtifactUI->AddChild(ArtifactDesc);
    // Set Background, Name and Description color
    switch (artifact.rarity)
    {
    case RarityTypes::Common:
        ArtifactBckgrd->SetColor(1, 1, 1);
        NameText->SetTextColor(0, 0, 0);
        DescText->SetTextColor(0, 0, 0);
        break;
    case RarityTypes::Rare:
        ArtifactBckgrd->SetColor(0, 1, 1);
        NameText->SetTextColor(0, 0, 0);
        DescText->SetTextColor(0, 0, 0);
        break;
    case RarityTypes::Lunary:
        ArtifactBckgrd->SetColor(0, 0, 1);
        NameText->SetTextColor(1, 1, 1);
        DescText->SetTextColor(1, 1, 1);
        break;
    case RarityTypes::Astral:
        ArtifactBckgrd->SetColor(1, 0, 0);
        NameText->SetTextColor(1, 1, 1);
        DescText->SetTextColor(1, 1, 1);
        break;
    case RarityTypes::Universal:
        ArtifactBckgrd->SetColor(1, 1, 0);
        NameText->SetTextColor(0, 0, 0);
        DescText->SetTextColor(0, 0, 0);
        break;
    default:
        ArtifactBckgrd->SetColor(1, 1, 1);
        NameText->SetTextColor(0, 0, 0);
        DescText->SetTextColor(0, 0, 0);
        break;
    }
    return ArtifactUI;
}