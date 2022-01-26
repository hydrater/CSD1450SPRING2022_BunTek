#include "MapGenerator.h"
#include "UI_DialogueHandler.h"
#include "DialogueDatabase.h"
#include "System.h"
#include <fstream>
#include <sstream>

void RemoveDialogue(Button* button);
void RemoveRewardSelection(Button* button);

UI_DialogueHandler* UI_DialogueHandler::instance = 0;

UI_DialogueHandler::UI_DialogueHandler(void)
{
}

UI_DialogueHandler::~UI_DialogueHandler(void)
{
}

UI_DialogueHandler& UI_DialogueHandler::Instance(void)
{
    if (instance != 0)
    {
        return *instance;
    }
    instance = new UI_DialogueHandler();
    return *instance;
}

void UI_DialogueHandler::Start(void)
{

}

void UI_DialogueHandler::Update(void)
{
    // For dialogue only
    if (selectedFlag == dialogueFlag)
    {
        if (dialogueNo >= dialogueList.size())
            return;

        if (AEInputCheckTriggered(AEVK_LBUTTON))
        {
            if (displayNo < dialogueList.size())
                doneDisplay = true;
            else
            {
                if (dialogueNo < dialogueList.size() - 1)
                {
                    ++dialogueNo;
                    WriteToDialogue();
                }
                else
                    CloseDialogueEvent();
            }
        }

        if (doneDisplay)
            dialogueTxt->SetText(dialogueOutput);
        else
        {
            if (dialogueNo < dialogueList.size())
            {
                displayTimer -= DeltaTime;

                if (displayTimer < 0 && !doneDisplay)
                {
                    if (displayNo < dialogueFinalDisplayTxt.size())
                        dialogueOutput.append(dialogueFinalDisplayTxt, displayNo++, 1);
                    else
                        doneDisplay = true;

                    dialogueTxt->SetText(dialogueOutput);

                    displayTimer = displaySpeed * DeltaTime;
                }
            }
        }
    }
}

void UI_DialogueHandler::CreateDialoguePreset(string flag, short sortingLayer)
{
    selectedFlag = flag;
    DeleteRewardSelection();
    DeleteDialogueEvent();

    if (selectedFlag == dialogueFlag || selectedFlag == encounterFlag)
    {
        CreateDialogue(selectedFlag, sortingLayer);
    }
    else if (selectedFlag == rewardFlag)
    {
        CreateRewardSelection(selectedFlag, sortingLayer);
    }
}

void UI_DialogueHandler::CreateDialogue(string flag, short sortingLayer) {

    //Create main dialogue box
    dialogueBox = new GameObject;
    GameObject* tempdialogue = devTools.CreateSpriteGameObject("UI/Texture.png", 1800, 360,
    AE_GFX_BM_BLEND, Vector2(0, -280), sortingLayer - 2);
    SpriteRenderer* tempRenderer = tempdialogue->GetComponent<SpriteRenderer>();
    tempRenderer->SetColor(0.7f, 0.7f, 0.7f);
    TextRenderer* tempTextRenderer = tempdialogue->AddComponent<TextRenderer>();
    tempTextRenderer->SetFont("Astral.ttf");
    tempTextRenderer->SetTextColor(1, 1, 1);
    tempTextRenderer->SetLayer(sortingLayer);
    dialogueBox->AddChild(tempdialogue);

    // Create actor box
    GameObject* tempGameObject = devTools.CreateSpriteGameObject("EncounterBox.png", tempRenderer->GetHalfWidth() * 2 / 4.5f, tempRenderer->GetHalfHeight() / 2,
        AE_GFX_BM_BLEND, Vector2(0.f, 0.f), sortingLayer - 1);
    SpriteRenderer* tempRenderer2 = tempGameObject->GetComponent<SpriteRenderer>();
    tempRenderer2->Owner()->transform->SetPosition(Vector2(
        tempRenderer->GetTransform()->worldposition.x - tempRenderer->GetHalfWidth() + tempRenderer2->GetHalfWidth(),
        tempRenderer->GetTransform()->worldposition.y + tempRenderer->GetHalfHeight() + tempRenderer2->GetHalfHeight())
    );
    dialogueBox->AddChild(tempGameObject);

    TextRenderer* tempTxtRenderer2 = tempGameObject->AddComponent<TextRenderer>();
    tempTxtRenderer2->SetFont("Astral.ttf");
    tempTxtRenderer2->SetTextColor(1, 1, 1);
    tempTxtRenderer2->SetLayer(1);
    tempTxtRenderer2->SetLayer(sortingLayer);

    // Buttons (Max 3)
    vector<Button*> buttonList;
    for (int i = 0; i < 3; ++i) {
        GameObject* tempButtonObj = devTools.CreateSpriteGameObject("UI/Button.png", tempRenderer->GetHalfWidth() * 2, tempRenderer->GetHalfHeight() / 2,
            2, Vector2(0.f, AEGfxGetWinMaxY() / 6 + (i * AEGfxGetWinMaxY() / 4)), sortingLayer - 1);
        SpriteRenderer* tempButtonRenderer = tempButtonObj->GetComponent<SpriteRenderer>();

        TextRenderer* tempButtonTxtRenderer = tempButtonObj->AddComponent<TextRenderer>();
        tempButtonTxtRenderer->SetFont("Gabriola.ttf");
        tempButtonTxtRenderer->SetTextColor(1, 1, 0);
        tempButtonTxtRenderer->SetText("SCREM");
        tempButtonTxtRenderer->SetScale(0.75f);
        tempButtonTxtRenderer->SetLayer(sortingLayer);
        tempButtonTxtRenderer->SetXAlignment(TextRenderer::xAlignmentTypes::Mid);
        tempButtonTxtRenderer->SetYAlignment(TextRenderer::yAlignmentTypes::Mid);

        Button* tempButton = tempButtonObj->AddComponent<Button>();
        tempButton->sr = tempButtonRenderer;
        tempButton->tr = tempButtonTxtRenderer;
        tempButton->affectedObject = dialogueBox;
        tempButton->ButtonEffect = &RemoveDialogue;

        dialogueBox->AddChild(tempButtonObj);
        buttonList.push_back(tempButton);
    }

    // Assign ObjReferences
    selectedFlag = flag;
    actorTxt = tempTxtRenderer2;
    dialogueTxt = tempTextRenderer;
    dialogueButtonList = buttonList;

    CloseDialogueEvent();

    StartDialogueEvent(flag);
}

void UI_DialogueHandler::StartDialogueEvent(string flag)
{
    LoadFromFile(flag);
    doneDisplay = false;
    displayTimer = 0;
    dialogueButtonNo = 0;
    actorTxt->Owner()->Activate();
    dialogueTxt->Owner()->Activate();
    for (int i = 0; i < dialogueButtonList.size(); ++i) {
        dialogueButtonList[i]->Owner()->Activate();
        dialogueButtonList[i]->Owner()->GetComponent<Button>()->SetClickable(true);
    }
    // Go through whole thing if it is an encounter
    if (flag == encounterFlag)
    {
        for (dialogueNo = 0; dialogueNo < dialogueList.size(); ++dialogueNo)
        {
            WriteToDialogue();
        }
    }
    // Go through once per click if it is a dialogue
    else if (flag == dialogueFlag)
    {
        WriteToDialogue();
    }
    // Deactivate non-used buttons
    for (; dialogueButtonNo < dialogueButtonList.size(); ++dialogueButtonNo)
        dialogueButtonList[dialogueButtonNo]->Owner()->Deactivate();
}

void UI_DialogueHandler::CloseDialogueEvent(void)
{
    if (actorTxt && dialogueTxt && dialogueButtonList[0])
    {
        actorTxt->Owner()->Deactivate();
        dialogueTxt->Owner()->Deactivate();
        for (int i = 0; i < dialogueButtonList.size(); ++i) {
            dialogueButtonList[i]->Owner()->Deactivate();
            dialogueButtonList[i]->Owner()->GetComponent<Button>()->SetClickable(false);
        }
    }
}

void UI_DialogueHandler::DeleteDialogueEvent(void)
{
    if (dialogueBox)
    {
        dialogueBox->Delete();
        dialogueBox = 0;
    }

    dialogueButtonList.clear();
}

void UI_DialogueHandler::LoadFromFile(string flag)
{
    string path = "./Assets/Dialogue.txt";

    ifstream input_file(path);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
            << path << "'" << endl;
        exit(EXIT_FAILURE);
    }

    string input = string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());

    vector<string> inputList;
    stringstream ss = stringstream{ input };
    bool canAdd = false;

    for (string line; getline(ss, line, '\n');)
        inputList.push_back(line);

    for (int i = 0; i < inputList.size(); ++i)
    {
        if (canAdd)
        {
            if (inputList[i] == "")
            {
                dialogueNo = 0;
                return;
            }
            else
                dialogueList.push_back(inputList[i]);
        }

        if (inputList[i] == flag)
            canAdd = true;
    }
}

void UI_DialogueHandler::WriteToDialogue(void)
{
    if (dialogueList[dialogueNo].rfind("/", 0) == 0)
    {
        if (dialogueList[dialogueNo].length() < 3)
        {
            cout << "Error: Comamnd has no parameters" << endl;
            return;
        }

        string parameters = dialogueList[dialogueNo].substr(3, dialogueList[dialogueNo].length());

        switch (dialogueList[dialogueNo][1])
        {
        case 'a':
            if (selectedFlag == dialogueFlag)
            {
                cout << "Actor Name: " << parameters << endl;
                name = parameters;
                actorTxt->SetText(name);
                ++dialogueNo;
                WriteToDialogue();
            }
            else if (selectedFlag == encounterFlag)
            {
                cout << "Encounter Name: " << parameters << endl;
                name = parameters;
                actorTxt->SetText(name);
            }
            break;

        case 'b':
            cout << "Button: " << parameters << endl;
            if (dialogueButtonNo < dialogueButtonList.size())
                dialogueButtonList[dialogueButtonNo++]->tr->SetText(parameters);
            break;

        case 'c':
            cout << "Choice: " << parameters << endl;
            if (rewardButtonNo < rewardButtonList.size())
                rewardButtonList[rewardButtonNo++]->tr->SetText(parameters);
            break;

        default:
            cout << "default line " << endl;
            break;
        }
    }
    else if (selectedFlag == dialogueFlag)
    {
        displayNo = 0;
        dialogueOutput = "";
        dialogueFinalDisplayTxt = dialogueList[dialogueNo];
        doneDisplay = false;
        
    }
    else if (selectedFlag == encounterFlag)
    {
        dialogueTxt->SetText(dialogueList[dialogueNo]);
        dialogueTxt->SetWarpAround(true);
    }
}

void UI_DialogueHandler::SetDialogueClickable(bool _canClick)
{
    for (int i = 0; i < dialogueButtonList.size(); ++i)
    {
        if (dialogueButtonList[i]->Owner() && dialogueButtonList[i]->Owner()->GetComponent<Button>())
            dialogueButtonList[i]->Owner()->GetComponent<Button>()->SetClickable(_canClick);
    }
}

void UI_DialogueHandler::CreateRewardSelection(string flag, short sortingLayer)
{
    Vector2 position = Vector2(0, 0);

    rewardSel = new GameObject;
    rewardSel->transform->SetPosition(position);

    // Background
    GameObject* tempBackground = devTools.CreateSpriteGameObject("Encounter.png", (float)AEGetWindowWidth(), (float)AEGetWindowHeight(), AE_GFX_BM_BLEND, Vector2(0, 0));
    tempBackground->GetComponent<SpriteRenderer>()->SetLayer(sortingLayer - 1);
    tempBackground->GetComponent<SpriteRenderer>()->SetTransparency(0.75f);
    rewardSel->AddChild(tempBackground);

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
    rewardSel->AddChild(tempHeader);

    // Buttons (3 selection and 1 skip)
    vector<Button*> tempbuttonList;
    for (int i = 0; i < 4; ++i) {

        GameObject* tempButtonObj = devTools.CreateSpriteGameObject("paddle.png", 350, 500, AE_GFX_BM_BLEND,
            Vector2(position.x, position.y - tempBackground->GetComponent<SpriteRenderer>()->GetHalfHeight() / 1.5f), sortingLayer - 1, 1.f);

        TextRenderer* tempButtonTxtRenderer = 0;
        tempButtonTxtRenderer = tempButtonObj->AddComponent<TextRenderer>();
        tempButtonTxtRenderer->SetFont("Gabriola.ttf");
        tempButtonTxtRenderer->SetTextColor(0, 0, 0);
        tempButtonTxtRenderer->SetText("I am a Reward");
        tempButtonTxtRenderer->SetScale(0.75f);
        tempButtonTxtRenderer->SetLayer(sortingLayer);
        tempButtonTxtRenderer->SetXAlignment(TextRenderer::xAlignmentTypes::Mid);
        tempButtonTxtRenderer->SetYAlignment(TextRenderer::yAlignmentTypes::Mid);

        Button* tempButton = tempButtonObj->AddComponent<Button>();
        tempButton->sr = tempButtonObj->GetComponent<SpriteRenderer>();
        tempButton->tr = tempButtonTxtRenderer;
        tempButton->affectedObject = rewardSel;
        tempButton->ButtonEffect = &RemoveRewardSelection;

        rewardSel->AddChild(tempButtonObj);
        tempbuttonList.push_back(tempButton);
        switch (i)
        {
        case 0:
            tempButtonObj->transform->SetPosition(Vector2(position.x, position.y));
            break;
        case 1:
            tempButtonObj->transform->SetPosition(Vector2(position.x - tempButton->sr->GetHalfWidth() * 3, position.y));
            break;
        case 2:
            tempButtonObj->transform->SetPosition(Vector2(position.x + tempButton->sr->GetHalfWidth() * 3, position.y));
            break;
        case 3:
            tempButton->sr->SetTexture("Buttons.png");
            tempButtonTxtRenderer->SetText("Skip to get sum guud seedz");
            tempButtonTxtRenderer->SetTextColor(1, 1, 0);
            tempButton->sr->Size(500, 150);
            break;
        }
    }
    
    header = tempHeader->GetComponent<SpriteRenderer>();
    background = tempBackground->GetComponent<SpriteRenderer>();
    headerText = tempHeaderTxtRenderer;
    rewardButtonList = tempbuttonList;

    CloseRewardSelection();

    StartRewardSelection(selectedFlag);
}

void UI_DialogueHandler::StartRewardSelection(string flag)
{
    LoadFromFile(flag);
    header->Owner()->Activate();
    background->Owner()->Activate();
    headerText->Owner()->Activate();
    rewardButtonNo = 0;
    for (int i = 0; i < rewardButtonList.size(); ++i)
        rewardButtonList[i]->Owner()->Activate();
    for (dialogueNo = 0; dialogueNo < dialogueList.size(); ++dialogueNo)
        WriteToDialogue();
    for (; rewardButtonNo < rewardButtonList.size() - 1; ++rewardButtonNo)
        rewardButtonList[rewardButtonNo]->Owner()->Deactivate();
}

void UI_DialogueHandler::CloseRewardSelection(void)
{
    header->Owner()->Deactivate();
    background->Owner()->Deactivate();
    headerText->Owner()->Deactivate();
    for (int i = 0; i < rewardButtonList.size(); ++i)
        rewardButtonList[i]->Owner()->Deactivate();
}

void UI_DialogueHandler::DeleteRewardSelection(void)
{
    if (rewardSel)
    {
        rewardSel->Delete();
        rewardSel = 0;
    }

    rewardButtonList.clear();
}

void RemoveRewardSelection(Button* button)
{
    UIDialogueManager.DeleteRewardSelection();
}

void RemoveDialogue(Button* button)
{
    UIDialogueManager.DeleteDialogueEvent();
    MapData.SetClickable(true);
    MapData.SetHoverable(true);
    MapData.DisplayNodeRoutes(MapData.playerTravelDistance);
}