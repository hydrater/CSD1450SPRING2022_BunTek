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

void UI_Shop::CreateShop(short sortingLayer, vector<string> artifacts, vector<string> stats)
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
            GameObject* tempButtonObj = devTools.CreateSpriteGameObject("Encounter.png", buttonArtifactSize.x, buttonArtifactSize.y, AE_GFX_BM_BLEND, Vector2(buttonArtifactPos[i].x, buttonArtifactPos[i].y));
            tempButtonObj->GetComponent<SpriteRenderer>()->SetLayer(sortingLayer - 1);
            tempButtonObj->GetComponent<SpriteRenderer>()->SetOpacity(0.5f);

            TextRenderer* tempButtonTxtRenderer = 0;
            tempButtonTxtRenderer = tempButtonObj->AddComponent<TextRenderer>();
            tempButtonTxtRenderer->SetFont("Gabriola.ttf");
            tempButtonTxtRenderer->SetTextColor(1, 1, 1);
            tempButtonTxtRenderer->SetText("Artifact");
            tempButtonTxtRenderer->SetFontScale(0.75f);
            tempButtonTxtRenderer->SetLayer(sortingLayer);
            tempButtonTxtRenderer->SetXAlignment(TextRenderer::xAlignmentTypes::Mid);
            tempButtonTxtRenderer->SetYAlignment(TextRenderer::yAlignmentTypes::Mid);

            Button* tempButton = tempButtonObj->AddComponent<Button>();
            tempButton->sr = tempButtonObj->GetComponent<SpriteRenderer>();
            tempButton->tr = tempButtonTxtRenderer;
            tempButton->affectedObject = shopUI;
            tempButton->ButtonEffect = &RemoveShop;

            shopUI->AddChild(tempButtonObj);
            tempbuttonArtifactList.push_back(tempButton);
        }
    }

    // Create Stats Holder
    GameObject* tempStatsHolder = devTools.CreateSpriteGameObject("Encounter.png", buttonArtifactSize.x * 2, buttonArtifactSize.y, AE_GFX_BM_BLEND, Vector2(0.f, -buttonArtifactSize.y / 2));
    tempStatsHolder->GetComponent<SpriteRenderer>()->SetLayer(sortingLayer - 1);
    tempStatsHolder->GetComponent<SpriteRenderer>()->SetOpacity(0.5f);

    // Create Stats Button
    vector<Button*> tempbuttonStatsList;
    for (int i = 0; i < stats.size(); ++i) {
        if (i < buttonStatsPos.size())
        {
            GameObject* tempButtonObj = devTools.CreateSpriteGameObject("Encounter.png", buttonStatsSize.x, buttonStatsSize.y, AE_GFX_BM_BLEND, Vector2(tempStatsHolder->transform->worldposition.x + buttonStatsPos[i].x, tempStatsHolder->transform->worldposition.y + buttonStatsPos[i].y));
            tempButtonObj->GetComponent<SpriteRenderer>()->SetLayer(sortingLayer - 1);
            tempButtonObj->GetComponent<SpriteRenderer>()->SetOpacity(0.5f);

            TextRenderer* tempButtonTxtRenderer = 0;
            tempButtonTxtRenderer = tempButtonObj->AddComponent<TextRenderer>();
            tempButtonTxtRenderer->SetFont("Gabriola.ttf");
            tempButtonTxtRenderer->SetTextColor(1, 1, 1);
            tempButtonTxtRenderer->SetText("Stats");
            tempButtonTxtRenderer->SetFontScale(0.75f);
            tempButtonTxtRenderer->SetLayer(sortingLayer);
            tempButtonTxtRenderer->SetXAlignment(TextRenderer::xAlignmentTypes::Mid);
            tempButtonTxtRenderer->SetYAlignment(TextRenderer::yAlignmentTypes::Mid);

            Button* tempButton = tempButtonObj->AddComponent<Button>();
            tempButton->sr = tempButtonObj->GetComponent<SpriteRenderer>();
            tempButton->tr = tempButtonTxtRenderer;
            tempButton->affectedObject = shopUI;
            tempButton->ButtonEffect = &RemoveShop;

            shopUI->AddChild(tempButtonObj);
            tempbuttonStatsList.push_back(tempButton);
        }
    }

    header = tempHeader->GetComponent<SpriteRenderer>();
    headerText = tempHeaderTxtRenderer;
    leaveButton = tempLeaveButton;
    buttonArtifactList = tempbuttonArtifactList;
    statsHolder = tempStatsHolder->GetComponent<SpriteRenderer>();
    buttonStatsList = tempbuttonStatsList;

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
    statsHolder->Owner()->Activate();
    for (int i = 0; i < buttonStatsList.size(); ++i)
        buttonStatsList[i]->Owner()->Activate();
}

void UI_Shop::CloseShop(void)
{
    header->Owner()->Deactivate();
    headerText->Owner()->Deactivate();
    leaveButton->Owner()->Deactivate();
    for (int i = 0; i < buttonArtifactList.size(); ++i)
        buttonArtifactList[i]->Owner()->Deactivate();
    statsHolder->Owner()->Deactivate();
    for (int i = 0; i < buttonStatsList.size(); ++i)
        buttonStatsList[i]->Owner()->Deactivate();
}

void UI_Shop::SetClickable(bool _canClick)
{
    for (int i = 0; i < buttonArtifactList.size(); ++i)
        buttonArtifactList[i]->Owner()->GetComponent<Button>()->SetClickable(_canClick);
    for (int i = 0; i < buttonStatsList.size(); ++i)
        buttonStatsList[i]->Owner()->GetComponent<Button>()->SetClickable(_canClick);
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