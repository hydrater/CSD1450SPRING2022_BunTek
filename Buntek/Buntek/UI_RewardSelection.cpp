#include "UI_RewardSelection.h"
#include "System.h"

//void RemoveRewardSelection(Button* button);

UI_RewardSelection::UI_RewardSelection(void)
{
}

UI_RewardSelection::~UI_RewardSelection(void)
{
}

void UI_RewardSelection::CreateRewardSelection(Vector2 position, int sortingLayer, vector<string> rewards)
{
    GameObject* rewardSelect = this->Owner();
    rewardSelect->transform->SetPosition(position);

    // Background
    GameObject* tempBackground = devTools.CreateSpriteGameObject("Encounter.png",(float) AEGetWindowWidth(), (float)AEGetWindowHeight(), AE_GFX_BM_BLEND, Vector2(0, 0));
    tempBackground->GetComponent<SpriteRenderer>()->SetLayer(sortingLayer - 1);
    tempBackground->GetComponent<SpriteRenderer>()->SetTransparency(0.75f);
    rewardSelect->AddChild(tempBackground);

    // Header
    GameObject* tempHeader = devTools.CreateSpriteGameObject("paddle.png", 800, 100, AE_GFX_BM_BLEND, Vector2(position.x, position.y + tempBackground->GetComponent<SpriteRenderer>()->GetHalfHeight() / 1.5f));
    tempHeader->GetComponent<SpriteRenderer>()->SetLayer(sortingLayer - 1);

    // HeaderText
    TextRenderer* tempHeaderTxtRenderer = 0;
    tempHeaderTxtRenderer = tempHeader->AddComponent<TextRenderer>();
    tempHeaderTxtRenderer->SetFont("Gabriola.ttf");
    tempHeaderTxtRenderer->SetTextColor(1, 0, 1);
    tempHeaderTxtRenderer->SetText("Choose Your Reward");
    tempHeaderTxtRenderer->SetLayer(sortingLayer);
    tempHeaderTxtRenderer->SetXAlignment(TextRenderer::xAlignmentTypes::Mid);
    tempHeaderTxtRenderer->SetYAlignment(TextRenderer::yAlignmentTypes::Mid);
    tempHeaderTxtRenderer->SetXBuffer(50);
    rewardSelect->AddChild(tempHeader);

    // Buttons (3 selection and 1 skip)
    vector<Button*> tempbuttonList;
    for (int i = 0; i < 4; ++i) {

        GameObject* tempButtonObj = devTools.CreateSpriteGameObject("paddle.png", 350, 500, AE_GFX_BM_BLEND, Vector2(position.x, position.y - tempBackground->GetComponent<SpriteRenderer>()->GetHalfHeight() / 1.5f));
        tempButtonObj->GetComponent<SpriteRenderer>()->SetLayer(sortingLayer - 1);

        TextRenderer* tempButtonTxtRenderer = 0;
        tempButtonTxtRenderer = tempButtonObj->AddComponent<TextRenderer>();
        tempButtonTxtRenderer->SetFont("Gabriola.ttf");
        tempButtonTxtRenderer->SetTextColor(1, 1, 0);
        tempButtonTxtRenderer->SetText("I am a Reward");
        tempButtonTxtRenderer->SetScale(0.75f);
        tempButtonTxtRenderer->SetLayer(sortingLayer);
        tempButtonTxtRenderer->SetXAlignment(TextRenderer::xAlignmentTypes::Mid);
        tempButtonTxtRenderer->SetYAlignment(TextRenderer::yAlignmentTypes::Mid);
        
        Button* tempButton = tempButtonObj->AddComponent<Button>();
        tempButton->sr = tempButtonObj->GetComponent<SpriteRenderer>();
        tempButton->tr = tempButtonTxtRenderer;/*
        tempButton->affectedObject = rewardSelect;
        tempButton->ButtonEffect = &RemoveRewardSelection;*/

        rewardSelect->AddChild(tempButtonObj);
        tempbuttonList.push_back(tempButton);
        switch (i)
        {
        case 0:
            tempButtonObj->transform->SetPosition(Vector2(position.x, position.y));
            break;
        case 1:
            tempButtonObj->transform->SetPosition(Vector2(position.x - tempButton->sr->GetHalfWidth()*3, position.y));
            break;
        case 2:
            tempButtonObj->transform->SetPosition(Vector2(position.x + tempButton->sr->GetHalfWidth()*3, position.y));
            break;
        case 3:
            tempButton->sr->SetTexture("Buttons.png");
            tempButtonTxtRenderer->SetText("Skip to get sum guud seedz");
            tempButton->sr->Size(500, 150);
            break;
        }
    }
    
    header = tempHeader->GetComponent<SpriteRenderer>();
    background = tempBackground->GetComponent<SpriteRenderer>();
    headerText = tempHeaderTxtRenderer;
    buttonList = tempbuttonList;

    CloseRewardSelection();

    StartRewardSelection();
}

void UI_RewardSelection::StartRewardSelection(void)
{
    header->Owner()->Activate();
    background->Owner()->Activate();
    headerText->Owner()->Activate();
    for (int i = 0; i < buttonList.size(); ++i)
        buttonList[i]->Owner()->Activate();
}

void UI_RewardSelection::CloseRewardSelection(void)
{
    header->Owner()->Deactivate();
    background->Owner()->Deactivate();
    headerText->Owner()->Deactivate();
    for (int i = 0; i < buttonList.size(); ++i)
        buttonList[i]->Owner()->Deactivate();
}

//void RemoveRewardSelection(Button* button)
//{
//    GameObject* tmp = button->affectedObject;
//    tmp->GetComponent<UI_RewardSelection>()->CloseRewardSelection();
//}