#include "UI_RewardSelection.h"
#include "System.h"

void RemoveRewardSelection(Button* button);

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
    GameObject* tempBackground = new GameObject();
    SpriteRenderer* tempBckgdRenderer = 0;
    tempBckgdRenderer = tempBackground->AddComponent<SpriteRenderer>();
    tempBckgdRenderer->Size(AEGetWindowWidth(), AEGetWindowHeight());
    tempBckgdRenderer->Owner()->transform->SetPosition(Vector2(0, 0));
    tempBckgdRenderer->SetTexture("EncounterBox.png");
    tempBckgdRenderer->SetLayer(sortingLayer - 1);
    tempBckgdRenderer->SetTransparency(0.75f);
    rewardSelect->AddChild(tempBackground);

    // Header
    GameObject* tempHeader = new GameObject();
    SpriteRenderer* tempHeaderRenderer = 0;
    tempHeaderRenderer = tempHeader->AddComponent<SpriteRenderer>();
    tempHeaderRenderer->Size(800, 100);
    tempHeaderRenderer->SetTexture("paddle.png");
    tempHeaderRenderer->SetLayer(sortingLayer - 1);
    tempHeader->transform->SetPosition(Vector2(position.x, position.y + tempBckgdRenderer->GetHalfHeight()/1.5f));

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
        GameObject* tempButtonObj = new GameObject();
        SpriteRenderer* tempButtonRenderer = 0;
        tempButtonRenderer = tempButtonObj->AddComponent<SpriteRenderer>();
        tempButtonRenderer->Size(350, 500);
        tempButtonRenderer->SetTexture("paddle.png");
        tempButtonRenderer->SetLayer(sortingLayer - 1);

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
        tempButton->sr = tempButtonRenderer;
        tempButton->tr = tempButtonTxtRenderer;
        tempButton->affectedObject = rewardSelect;
        tempButton->ButtonEffect = &RemoveRewardSelection;

        rewardSelect->AddChild(tempButtonObj);
        tempbuttonList.push_back(tempButton);
        switch (i)
        {
        case 0:
            tempButtonObj->transform->SetPosition(Vector2(position.x, position.y));
            break;
        case 1:
            tempButtonObj->transform->SetPosition(Vector2(position.x - tempButtonRenderer->GetHalfWidth()*3, position.y));
            break;
        case 2:
            tempButtonObj->transform->SetPosition(Vector2(position.x + tempButtonRenderer->GetHalfWidth()*3, position.y));
            break;
        case 3:
            tempButtonRenderer->SetTexture("Buttons.png");
            tempButtonTxtRenderer->SetText("Skip to get sum guud seedz");
            tempButtonRenderer->Size(500, 150);
            tempButtonObj->transform->SetPosition(Vector2(position.x, position.y - tempBckgdRenderer->GetHalfHeight() / 1.5f));
            break;
        }
    }
    
    header = tempHeaderRenderer;
    background = tempBckgdRenderer;
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

void RemoveRewardSelection(Button* button)
{
    GameObject* tmp = button->affectedObject;
    tmp->GetComponent<UI_RewardSelection>()->CloseRewardSelection();
}