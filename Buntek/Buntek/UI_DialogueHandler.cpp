#include "MapGenerator.h"
#include "ArtifactDatabase.h"
#include "GameManager.h"
#include "SaveManager.h"
#include "UI_DialogueHandler.h"
#include "DialogueDatabase.h"
#include "System.h"
#include <fstream>
#include <sstream>

void RemoveDialogue(Button* button);
void BF_ChooseLootButton(Button* button);
void BF_Sample1Button(Button* button);
void BF_HealHalfButton(Button* button);
void BF_HealFullButton(Button* button);
void CF_PickUpArtifactButton(Button* button);
void CF_Sample1Button(Button* button);

UI_DialogueHandler::UI_DialogueHandler(void)
{
}

UI_DialogueHandler::~UI_DialogueHandler(void)
{
}

UI_DialogueHandler& UI_DialogueHandler::Instance(void)
{
    static UI_DialogueHandler instance;
    return instance;
}

void UI_DialogueHandler::Update(void)
{
    // For dialogue only
    if (UIOpen)
    {
        if (dialogueNo >= dialogueList.size())
            return;

        if (AEInputCheckTriggered(AEVK_LBUTTON) && !UIDecision)
        {
            if (displayNo < dialogueFinalDisplayTxt.size())
                doneDisplay = true;
            else
            {
                if (dialogueNo < dialogueList.size() - 1)
                {
                    ++dialogueNo;
                    WriteToDialogue();
                }
                else
                    RemoveDialogue(nullptr);
            }
        }

        if (doneDisplay)
        {
            dialogueTxt->SetText(dialogueFinalDisplayTxt);
            displayNo = (int)dialogueFinalDisplayTxt.size();

            // Skip to next display if the next command is either a button or a reward selection
            int nextDialogueNo = dialogueNo + 1;
            if (CheckNextCommand('b') || CheckNextCommand('c'))
            {
                ++dialogueNo;
                WriteToDialogue();
            }
        }
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
    DialogueDatabase.ClearDialogueSceneObjs();
    DeleteDialogueEvent();

    UIOpen = true;
    UIDecision = false;
    CreateDialogue(selectedFlag, sortingLayer);
}

void UI_DialogueHandler::CreateRewardSelPreset(vector<Artifact> artifact, short sortingLayer, bool canDecline)
{
    selectedFlag = "";
    DialogueDatabase.ClearDialogueSceneObjs();
    DeleteDialogueEvent();

    UIOpen = true;
    UIDecision = true;
    CreateRewardSel(artifact, sortingLayer, canDecline);
}

// ---------------------------------------------------------NORMAL DIALOGUE---------------------------------------------------------
void UI_DialogueHandler::CreateDialogue(string flag, short sortingLayer) {

    CreatePreset(sortingLayer);

    selectedFlag = flag;
    StartDialogueEvent(flag);
}

void UI_DialogueHandler::StartDialogueEvent(string flag)
{
    LoadFromFile(flag);
    doneDisplay = false;
    actorTxt->Owner()->Activate();
    dialogueTxt->Owner()->Activate();
    for (int i = 0; i < dialogueButtonList.size(); ++i) {
        dialogueButtonList[i]->Owner()->Activate();
        dialogueButtonList[i]->Owner()->GetComponent<Button>()->SetClickable(true);
    }
    for (int i = 0; i < rewardButtonList.size(); ++i) {
        rewardButtonList[i]->Owner()->Activate();
        rewardButtonList[i]->Owner()->GetComponent<Button>()->SetClickable(true);
    }
    WriteToDialogue();
    
    // Deactivate non-used buttons
    for (int i = dialogueButtonNo; i < dialogueButtonList.size(); ++i)
        dialogueButtonList[i]->Owner()->Deactivate();
    // Deactivate non-used rewards
    for (int i = rewardButtonNo; i < rewardButtonList.size(); ++i)
        rewardButtonList[i]->Owner()->Deactivate();

}

void UI_DialogueHandler::SkipDialogue(void)
{
    if (displayNo < dialogueFinalDisplayTxt.size())
        doneDisplay = true;
    else
    {
        if (dialogueNo < dialogueList.size() - 1)
        {
            ++dialogueNo;
            WriteToDialogue();
        }
        else
            RemoveDialogue(nullptr);
    }
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

    dialogueList.clear();

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
    if (dialogueNo >= dialogueList.size())
        return;

    if (dialogueList[dialogueNo].rfind("/", 0) == 0)
    {
        if (dialogueList[dialogueNo].length() < 4)
        {
            cout << "Error: Comamnd has no parameters" << endl;
            return;
        }

        string parameters = dialogueList[dialogueNo].substr(4, dialogueList[dialogueNo].length());

        switch (dialogueList[dialogueNo][1])
        {
        case 'a':
            //cout << "Actor Name: " << parameters << endl;
            name = parameters;
            actorTxt->SetText(name);
            // Assign color
            switch (dialogueList[dialogueNo][2])
            {
            case 'a': // Abyss (black)
                actorTxt->SetTextColor(0, 0, 0);
                break;
            case 'b': // Blue
                actorTxt->SetTextColor(0, 0, 1);
                break;
            case 'g': // Green
                actorTxt->SetTextColor(0, 1, 0);
                break;
            case 'c': // Cyan
                actorTxt->SetTextColor(0, 1, 1);
                break;
            case 'r': // Red
                actorTxt->SetTextColor(1, 0, 0);
                break;
            case 'p': // Purple
                actorTxt->SetTextColor(1, 0, 1);
                break;
            case 'y': // Yellow
                actorTxt->SetTextColor(1, 1, 0);
                break;
            case 'w': // White
                actorTxt->SetTextColor(1, 1, 1);
                break;
            default:  // Purple
                actorTxt->SetTextColor(1, 0, 1);
                break;
            }
            ++dialogueNo;
            WriteToDialogue();
            break;

        case 'b':
            //cout << "Button: " << parameters << endl;
            if (dialogueButtonNo < dialogueButtonList.size())
            {
                AssignButton(dialogueButtonList[dialogueButtonNo], 'b', dialogueList[dialogueNo][2]);

                // Check if player can select this button (Can afford price)
                if (dialogueButtonList[dialogueButtonNo]->ButtonEffect == &BF_HealFullButton && GameManager.playerProfile.stardust < fullHealthCost)
                {
                    dialogueButtonList[dialogueButtonNo]->Owner()->GetComponent<SpriteRenderer>()->SetOpacity(0.5f);
                    dialogueButtonList[dialogueButtonNo]->Deactivate();
                }

                dialogueButtonList[dialogueButtonNo]->tr->SetText(parameters);
                dialogueButtonList[dialogueButtonNo++]->Owner()->Activate();
                UIDecision = true;
                if (CheckNextCommand('b'))
                {
                    ++dialogueNo;
                    WriteToDialogue();
                }
            }
            break;

        case 'c':
            //cout << "Choice: " << parameters << endl;
            if (rewardButtonNo < rewardButtonList.size())
            {
                AssignButton(rewardButtonList[rewardButtonNo], 'c', dialogueList[dialogueNo][2]);
                // If it is the last button [Decline choices]
                if (rewardButtonNo < rewardButtonList.size() - 1)
                    AssignArtifact(rewardButtonList[rewardButtonNo]->Owner(), parameters);
                else
                    rewardButtonList[rewardButtonNo]->tr->SetText(parameters);
                rewardButtonList[rewardButtonNo++]->Owner()->Activate();
                UIDecision = true;
                if (CheckNextCommand('c'))
                {
                    ++dialogueNo;
                    WriteToDialogue();
                }
            }
            break;

        case 'd':
            //cout << "Init scene " << parameters << endl;
            DialogueDatabase.InitDialogueScene(parameters);
            ++dialogueNo;
            WriteToDialogue();
            break;

        default:
            cout << "default line " << endl;
            break;
        }
    }
    else
    {
        displayNo = 0;
        dialogueOutput = "";
        dialogueFinalDisplayTxt = dialogueList[dialogueNo];
        //cout << "Dialogue: " << dialogueFinalDisplayTxt << endl;
        doneDisplay = false;
    }
}

// ---------------------------------------------------------REWARDS DIALOGUE---------------------------------------------------------
void UI_DialogueHandler::CreateRewardSel(vector<Artifact> artifact, short sortingLayer, bool canDecline)
{
    CreatePreset(sortingLayer);

    // Create Reward Selection Actor and Description
    actorTxt->Owner()->Activate();
    actorTxt->SetText("Battle End");
    dialogueTxt->Owner()->Activate();
    dialogueTxt->SetText("Choose your loot");
    dialogueFinalDisplayTxt = "Choose your loot";

    // Assign artifacts [Max: 3]
    for (int i = 0; i < rewardButtonList.size() - 1; ++i) {
        rewardButtonList[i]->Owner()->Activate();
        // Assign artifact
        if (i <= artifact.size() - 1)
        {
            GameObject* owner = rewardButtonList[i]->Owner();
            GameObject* tempArtifact = devTools.CreateArtifactUIGameObject(artifact[i].ID, AE_GFX_BM_BLEND,
                owner->transform->worldposition, owner->GetComponent<SpriteRenderer>()->GetLayer());
            owner->GetComponent<SpriteRenderer>()->SetOpacity(0);
            owner->AddChild(tempArtifact);
            ArtifactLoot Artifact;
            Artifact.DisplayArtifactOwner = owner;
            Artifact.ArtifactID = artifact[i].ID;
            ArtifactChoices.push_back(Artifact);
            // Assign Button Effect
            AssignButton(rewardButtonList[i], 'c', CF_PickUpArtifact + '0');
        }
    }

    // Auto activate decline choice [ALWAYS last choice]
    if (canDecline && rewardButtonList.size() > 0)
    {
        rewardButtonList[rewardButtonList.size() - 1]->Owner()->Activate();
        AssignButton(rewardButtonList[rewardButtonList.size() - 1], 'c', CF_Leave + '0');
    }
}

// --------------------------------------------------------- DIALOGUE TOOL ---------------------------------------------------------
void UI_DialogueHandler::DeleteDialogueEvent(void)
{
    if (dialogueBox)
    {
        dialogueBox->Delete();
        dialogueBox = 0;
    }

    dialogueButtonList.clear();
    rewardButtonList.clear();
    ArtifactChoices.clear();
}

string UI_DialogueHandler::GenerateRandomDialogueID(void)
{
    string id = "E";
    id += "00" + to_string(RandIntMinMax(0, 1));
    return id;
}

void UI_DialogueHandler::CreatePreset(short sortingLayer)
{
    //Create main dialogue box
    dialogueBox = new GameObject;
    GameObject* tempdialogue = devTools.CreateSpriteGameObject("UI/DialogueBox.png", 1900, 303,
        AE_GFX_BM_BLEND, Vector2(0, -370), sortingLayer - 2);
    SpriteRenderer* tempRenderer = tempdialogue->GetComponent<SpriteRenderer>();
    TextRenderer* tempTextRenderer = tempdialogue->AddComponent<TextRenderer>();
    tempTextRenderer->SetFont("GothicA1.ttf");
    tempTextRenderer->SetFontScale(0.6f);
    tempTextRenderer->SetTextColor(1, 1, 1);
    tempTextRenderer->SetLayer(sortingLayer);
    dialogueBox->AddChild(tempdialogue);

    // Create actor box
    GameObject* tempGameObject = devTools.CreateSpriteGameObject("UI/DialogueBox.png", tempRenderer->GetHalfWidth() * 2 / 4.5f, tempRenderer->GetHalfHeight() / 2,
        AE_GFX_BM_BLEND, Vector2(0.f, 0.f), sortingLayer - 1);
    SpriteRenderer* tempRenderer2 = tempGameObject->GetComponent<SpriteRenderer>();
    tempRenderer2->SetOpacity(0);
    tempRenderer2->Owner()->transform->SetPosition(Vector2(
        0.0f,
        tempRenderer->GetTransform()->worldposition.y + tempRenderer2->GetHalfHeight() + 20)
    );
    dialogueBox->AddChild(tempGameObject);

    TextRenderer* tempTxtRenderer2 = tempGameObject->AddComponent<TextRenderer>();
    tempTxtRenderer2->SetFont("Gabriola.ttf");
    tempTxtRenderer2->SetTextColor(1.0f, 0.29f, 0.89f);
    tempTxtRenderer2->SetLayer(1);
    tempTxtRenderer2->SetLayer(sortingLayer);

    // Buttons (Max 3)
    vector<Button*> buttonList;
    for (int i = 0; i < 3; ++i) {
        GameObject* tempButtonObj = devTools.CreateSpriteGameObject("UI/Button.png", 785, 70,
            AE_GFX_BM_BLEND, Vector2(0.f, AEGfxGetWinMaxY() / 3 - (i * AEGfxGetWinMaxY() / 4)), sortingLayer - 1);
        SpriteRenderer* tempButtonRenderer = tempButtonObj->GetComponent<SpriteRenderer>();
        tempButtonRenderer->SetOpacity(0.8f);

        TextRenderer* tempButtonTxtRenderer = tempButtonObj->AddComponent<TextRenderer>();
        tempButtonTxtRenderer->SetFont("Gabriola.ttf");
        tempButtonTxtRenderer->SetTextColor(1, 1, 1);
        tempButtonTxtRenderer->SetFontScale(0.75f);
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


    // Rewards Choices (3 selection and 1 skip)
    vector<Button*> tempbuttonList;
    for (int i = 0; i < 4; ++i) {

        GameObject* tempButtonObj = devTools.CreateSpriteGameObject("paddle.png", 350, 500, AE_GFX_BM_BLEND,
            Vector2(0.f, -AEGfxGetWinMaxY() / 3.f), sortingLayer - 1);

        TextRenderer* tempButtonTxtRenderer = devTools.AddTextToSpriteGameObject(tempButtonObj, "Gabriola.ttf", "", TextRenderer::xAlignmentTypes::Mid, TextRenderer::yAlignmentTypes::Mid, 36.f, sortingLayer);
        tempButtonTxtRenderer->SetTextColor(0, 0, 0);

        Button* tempButton = tempButtonObj->AddComponent<Button>();
        tempButton->sr = tempButtonObj->GetComponent<SpriteRenderer>();
        tempButton->tr = tempButtonTxtRenderer;
        tempButton->affectedObject = dialogueBox;
        tempButton->ButtonEffect = &RemoveDialogue;

        dialogueBox->AddChild(tempButtonObj);
        tempbuttonList.push_back(tempButton);
        switch (i)
        {
        case 0:
            tempButtonObj->transform->SetPosition(Vector2(0.f, tempButton->sr->GetHalfHeight() / 1.5f));
            break;
        case 1:
            tempButtonObj->transform->SetPosition(Vector2(-tempButton->sr->GetHalfWidth() * 3, tempButton->sr->GetHalfHeight() / 1.5f));
            break;
        case 2:
            tempButtonObj->transform->SetPosition(Vector2(tempButton->sr->GetHalfWidth() * 3, tempButton->sr->GetHalfHeight() / 1.5f));
            break;
        case 3:
            tempButton->sr->SetTexture("Buttons.png");
            tempButtonTxtRenderer->SetText("Skip to get sum guud seedz");
            tempButtonTxtRenderer->SetTextColor(1, 1, 0);
            tempButton->sr->Size(500, 150);
            break;
        }
    }

    // Assign ObjReferences
    actorTxt = tempTxtRenderer2;
    dialogueTxt = tempTextRenderer;
    dialogueButtonList = buttonList;
    rewardButtonList = tempbuttonList;

    if (actorTxt && dialogueTxt && dialogueButtonList.size() > 0 && rewardButtonList.size() > 0)
    {
        actorTxt->Owner()->Deactivate();
        dialogueTxt->Owner()->Deactivate();
        for (int i = 0; i < dialogueButtonList.size(); ++i) {
            dialogueButtonList[i]->Owner()->Deactivate();
            dialogueButtonList[i]->Owner()->GetComponent<Button>()->SetClickable(false);
        }
        for (int i = 0; i < rewardButtonList.size(); ++i) {
            rewardButtonList[i]->Owner()->Deactivate();
            rewardButtonList[i]->Owner()->GetComponent<Button>()->SetClickable(false);
        }
    }

    // Reset Variables
    doneDisplay = true;
    displayTimer = 0;
    displayNo = 0;
    dialogueFinalDisplayTxt = "";
    dialogueButtonNo = 0;
    rewardButtonNo = 0;
}

bool UI_DialogueHandler::CheckNextCommand(char command)
{
    int nextDialogueNo = dialogueNo + 1;
    return (nextDialogueNo < dialogueList.size() && (dialogueList[nextDialogueNo][0] == '/') && (dialogueList[nextDialogueNo][1] == command));
}

void UI_DialogueHandler::SetDialogueClickable(bool _canClick)
{
    for (int i = 0; i < dialogueButtonList.size(); ++i)
    {
        if (dialogueButtonList[i]->Owner() && dialogueButtonList[i]->Owner()->GetComponent<Button>())
            dialogueButtonList[i]->Owner()->GetComponent<Button>()->SetClickable(_canClick);
    }
    for (int i = 0; i < rewardButtonList.size(); ++i)
    {
        if (rewardButtonList[i]->Owner() && rewardButtonList[i]->Owner()->GetComponent<Button>())
            rewardButtonList[i]->Owner()->GetComponent<Button>()->SetClickable(_canClick);
    }
}

void UI_DialogueHandler::AssignButton(Button* button, char buttonType, char selchar)
{
    if (!isdigit(selchar))
        return;
    int decision = (int)(selchar - '0');

    // Decide result based on buttonType and decision
    // Encounter Button
    if (buttonType == 'b')
    {
        switch (decision)
        {
        case BF_Leave:
            button->ButtonEffect = &RemoveDialogue;
            break;
        case BF_ChooseLoot:
            button->ButtonEffect = &BF_ChooseLootButton;
            break;
        case BF_HealHalf:
            button->ButtonEffect = &BF_HealHalfButton;
            break;
        case BF_HealFull:
            button->ButtonEffect = &BF_HealFullButton;
            break;
        case BF_Sample1:
            button->ButtonEffect = &BF_Sample1Button;
            break;
        default:
            button->ButtonEffect = &RemoveDialogue;
            break;
        }
    }
    // Reward Choice
    else if (buttonType == 'c')
    {
        switch (decision)
        {
        case CF_Leave:
            button->ButtonEffect = &RemoveDialogue;
            break;
        case CF_PickUpArtifact:
            button->ButtonEffect = &CF_PickUpArtifactButton;
            break;
        case CF_Sample1:
            button->ButtonEffect = &CF_Sample1Button;
            break;
        default:
            button->ButtonEffect = &RemoveDialogue;
            break;
        }
    }
}

void UI_DialogueHandler::AssignArtifact(GameObject* owner, string selArtifact)
{
    // Take first three letters from the string
    unsigned long ID = 0;
    if (selArtifact[0] >= '0' && selArtifact[0] <= '9' && selArtifact[1] >= '0' && selArtifact[1] <= '9'
        && selArtifact[2] >= '0' && selArtifact[2] <= '9' && selArtifact[3] >= '0' && selArtifact[3] <= '9')
        ID = (selArtifact[0] - '0') * 1000 + (selArtifact[1] - '0') * 100 + (selArtifact[2] - '0') * 10 + (selArtifact[3] - '0');
    GameObject* tempArtifact = devTools.CreateArtifactUIGameObject(ID, AE_GFX_BM_BLEND,
            owner->transform->worldposition, owner->GetComponent<SpriteRenderer>()->GetLayer());
    owner->GetComponent<SpriteRenderer>()->SetOpacity(0);
    owner->AddChild(tempArtifact);
    ArtifactLoot Artifact;
    Artifact.DisplayArtifactOwner = owner;
    Artifact.ArtifactID = ID;
    ArtifactChoices.push_back(Artifact);
}

void RemoveDialogue(Button* button)
{
    UIDialogueManager.DeleteDialogueEvent();
    MapData.SetClickable(true);
    MapData.SetHoverable(true);
    MapData.DisplayNodeRoutes(MapData.playerTravelDistance);
    UIDialogueManager.UIOpen = false;
    UIDialogueManager.UIDecision = false;
    DialogueDatabase.ClearDialogueSceneObjs();
}

// ---------------------------------------------------------BUTTON FUNCTIONS---------------------------------------------------------
void BF_ChooseLootButton(Button* button)
{
    // [TODO! Obtain the possible loot choice and assign it to the creation]
    Artifact test1, test2, test3;
    test1.ID = 400;
    test2.ID = 400;
    test3.ID = 400;
    vector<Artifact> fakeArtifacts{ test1, test2, test3};
    // Creates a choose loot / rng loot
    UIDialogueManager.CreateRewardSelPreset(fakeArtifacts, 3, true);
}
void BF_HealHalfButton(Button* button)
{
    // Heal player by 50%
    GameManager.playerProfile.hp += GameManager.playerProfile.maxhp / 2;

    if (GameManager.playerProfile.hp > GameManager.playerProfile.maxhp)
        GameManager.playerProfile.hp = GameManager.playerProfile.maxhp;
    RemoveDialogue(button);
}
void BF_HealFullButton(Button* button)
{
    // Heal player by Full by using stardust
    GameManager.playerProfile.stardust -= UIDialogueManager.fullHealthCost;
    GameManager.playerProfile.hp = GameManager.playerProfile.maxhp;
    RemoveDialogue(button);
}
void BF_Sample1Button(Button* button)
{
    // Sample 1 Go to Reward Selection
    UIDialogueManager.CreateDialoguePreset("rsel", 3);
}

// ---------------------------------------------------------CHOICE FUNCTIONS---------------------------------------------------------
void CF_PickUpArtifactButton(Button* button)
{
    // Add artifact to the player's Artifact List
    GameObject* owner = button->Owner();
    unsigned long ID = 0;
    for (int i{ 0 }; i < UIDialogueManager.ArtifactChoices.size() ; ++i)
    {
        if (owner == UIDialogueManager.ArtifactChoices[i].DisplayArtifactOwner)
        {
            ID = UIDialogueManager.ArtifactChoices[i].ArtifactID;
            break;
        }
    }
    // Assign to allocated vector
    SaveManager.AddToArtifactList(ID);
    RemoveDialogue(button);
}
void CF_Sample1Button(Button* button)
{
    // Sample 1 Go to Dialogue
    UIDialogueManager.CreateDialoguePreset("asd", 3);
}