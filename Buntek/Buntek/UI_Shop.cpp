#include "MapGenerator.h"
#include "UI_Shop.h"
#include "Devtools.h"
#include "System.h"

void RemoveShop(Button* button);

UI_Shop::UI_Shop(void)
{
}

UI_Shop::~UI_Shop(void)
{
}

void UI_Shop::CreateShop(short sortingLayer, vector<Artifact> artifacts)
{
    GameObject* shopUI = this->Owner();

    // Header
    GameObject* tempHeader = devTools.CreateSpriteGameObject("Encounter.png", 600, 150, AE_GFX_BM_BLEND, Vector2(0.f, AEGetWindowHeight() / 2.5f),(short)(sortingLayer - 1), 0.5f);
   

    // HeaderText
    TextRenderer* tempHeaderTxtRenderer = 0;
    tempHeaderTxtRenderer = tempHeader->AddComponent<TextRenderer>();
    tempHeaderTxtRenderer->SetFont("Gabriola.ttf");
    tempHeaderTxtRenderer->SetTextColor(1, 1, 1);
    tempHeaderTxtRenderer->SetText("Shop");
    tempHeaderTxtRenderer->SetLayer(sortingLayer);
    tempHeaderTxtRenderer->SetXAlignment(TextRenderer::xAlignmentTypes::Mid);
    tempHeaderTxtRenderer->SetYAlignment(TextRenderer::yAlignmentTypes::Mid);
    tempHeaderTxtRenderer->SetXBuffer(50);
    shopUI->AddChild(tempHeader);

    // Leave Button
    GameObject* tempLeave = devTools.CreateSpriteGameObject("Buttons.png", 500, 100, AE_GFX_BM_BLEND, Vector2(0.f, -AEGetWindowHeight() / 3.f));
    TextRenderer* tempLeaveTxtRenderer = 0;
    tempLeaveTxtRenderer = tempLeave->AddComponent<TextRenderer>();
    tempLeaveTxtRenderer->SetFont("Gabriola.ttf");
    tempLeaveTxtRenderer->SetTextColor(1, 1, 1);
    tempLeaveTxtRenderer->SetText("Leave");
    Button* tempLeaveButton = tempLeave->AddComponent<Button>();
    tempLeaveButton->sr = tempLeave->GetComponent<SpriteRenderer>();
    tempLeaveButton->tr = tempLeaveTxtRenderer;
    tempLeaveButton->affectedObject = shopUI;
    tempLeaveButton->ButtonEffect = &RemoveShop;
    shopUI->AddChild(tempLeave);

    // Shop Artifacts Buttons
    vector<Button*> tempbuttonArtifactList;
    for (int i = 0; i < artifacts.size(); ++i) {
        if (i < buttonArtifactPos.size())
        {
            GameObject* tempButtonObj = devTools.CreateArtifactUIGameObject(artifacts[i], buttonArtifactSize.x, buttonArtifactSize.y, AE_GFX_BM_BLEND,
                Vector2(buttonArtifactPos[i].x, buttonArtifactPos[i].y), sortingLayer - 1);

            Button* tempButton = tempButtonObj->AddComponent<Button>();
            tempButton->sr = tempButtonObj->GetComponent<SpriteRenderer>();
            tempButton->tr = tempButtonObj->GetComponent<TextRenderer>();
            tempButton->affectedObject = shopUI;
            tempButton->ButtonEffect = &RemoveShop;

            shopUI->AddChild(tempButtonObj);
            tempbuttonArtifactList.push_back(tempButton);
        }
    }

    header = tempHeader->GetComponent<SpriteRenderer>();
    headerText = tempHeaderTxtRenderer;
    leaveButton = tempLeaveButton;
    buttonArtifactList = tempbuttonArtifactList;

    CloseShop();

    StartShop();

    SetClickable(false);
}

void UI_Shop::StartShop(void)
{
    header->Owner()->Activate();
    headerText->Owner()->Activate();
    leaveButton->Owner()->Activate();
    for (int i = 0; i < buttonArtifactList.size(); ++i)
        buttonArtifactList[i]->Owner()->Activate();
}

void UI_Shop::CloseShop(void)
{
    header->Owner()->Deactivate();
    headerText->Owner()->Deactivate();
    leaveButton->Owner()->Deactivate();
    for (int i = 0; i < buttonArtifactList.size(); ++i)
        buttonArtifactList[i]->Owner()->Deactivate();
}

void UI_Shop::SetClickable(bool _canClick)
{
    for (int i = 0; i < buttonArtifactList.size(); ++i)
        buttonArtifactList[i]->Owner()->GetComponent<Button>()->SetClickable(_canClick);
}

void RemoveShop(Button* button)
{
    GameObject* tmp = button->affectedObject;
    tmp->GetComponent<UI_Shop>()->CloseShop();
    MapData.SetClickable(true);
    MapData.SetHoverable(true);
    MapData.DisplayNodeRoutes(MapData.playerTravelDistance);
    if (MapData.shopUI)
        MapData.shopUI->Delete();
    MapData.shopUI = 0;
}