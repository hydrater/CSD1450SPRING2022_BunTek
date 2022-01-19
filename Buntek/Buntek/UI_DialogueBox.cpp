#include "UI_DialogueBox.h"
#include "System.h"
#include <fstream>
#include <sstream>

UI_DialogueBox::UI_DialogueBox(void)
{
}

UI_DialogueBox::~UI_DialogueBox(void)
{
}

void UI_DialogueBox::Start(void)
{
    
}

void UI_DialogueBox::Update(void)
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

void UI_DialogueBox::CreateDialogue(string flag) {

    GameObject* dialogue = this->Owner();
    //Create main dialogue box
    SpriteRenderer* tempRenderer = 0;
    TextRenderer* tempTextRenderer = 0;
    dialogue->transform->SetPosition(Vector2(0, -280));
    tempRenderer = dialogue->AddComponent<SpriteRenderer>();
    tempRenderer->Size(1800, 360);
    tempRenderer->SetTexture("UI/Texture.png");
    tempRenderer->SetColor(0.7f, 0.7f, 0.7f);
    tempRenderer->SetLayer(1);
    tempTextRenderer = dialogue->AddComponent<TextRenderer>();
    tempTextRenderer->SetFont("Astral.ttf");
    tempTextRenderer->SetTextColor(1, 1, 1);
    tempTextRenderer->SetLayer(1);

    // Create actor box
    SpriteRenderer* tempRenderer2 = 0;
    TextRenderer* tempTxtRenderer2 = 0;
    GameObject* tempGameObject = devTools.CreateSpriteGameObject("EncounterBox.png", tempRenderer->GetHalfWidth() * 2 / 4.5f, tempRenderer->GetHalfHeight() / 2,
        AE_GFX_BM_BLEND, Vector2(0.f, 0.f));
    tempRenderer2 = tempGameObject->GetComponent<SpriteRenderer>();

    tempTxtRenderer2 = tempGameObject->AddComponent<TextRenderer>();
    tempTxtRenderer2->SetFont("Astral.ttf");
    tempTxtRenderer2->SetTextColor(1, 1, 1);
    tempTxtRenderer2->SetLayer(1);

    // Create UI_DialogueBox and assign
    UI_DialogueBox* tempdialogue = tempGameObject->AddComponent<UI_DialogueBox>();
    tempdialogue->AssignObjReferences(tempRenderer2, tempRenderer, tempTxtRenderer2, tempTextRenderer);
    tempdialogue->StartDialogueEvent(flag);
}

void UI_DialogueBox::AssignObjReferences(SpriteRenderer* _actorSprite, SpriteRenderer* _dialogueSprite, TextRenderer* _actorTxt, TextRenderer* _dialogueTxt)
{
    actorTxt = _actorTxt;
    dialogueTxt = _dialogueTxt;

    _actorSprite->Owner()->transform->SetPosition(Vector2(
        _dialogueSprite->GetTransform()->worldposition.x - _dialogueSprite->GetHalfWidth() + _actorSprite->GetHalfWidth(),
        _dialogueSprite->GetTransform()->worldposition.y + _dialogueSprite->GetHalfHeight() + _actorSprite->GetHalfHeight())
    );

    actorTxt->Owner()->Deactivate();
    dialogueTxt->Owner()->Deactivate();
}

void UI_DialogueBox::StartDialogueEvent(string flag)
{
    LoadFromFile(flag);
    doneDisplay = false;
    displayTimer = 0;
    WriteToDialogue();
    actorTxt->Owner()->Activate();
    dialogueTxt->Owner()->Activate();
}

void UI_DialogueBox::CloseDialogueEvent(void)
{
    actorTxt->Owner()->Deactivate();
    dialogueTxt->Owner()->Deactivate();
}

void UI_DialogueBox::LoadFromFile(string flag)
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
    stringstream ss = stringstream{input};
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

void UI_DialogueBox::WriteToDialogue(void)
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
            cout << "Actor Name: " << parameters << endl;
            name = parameters;
            actorTxt->SetText(name);
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
        doneDisplay = false;
    }
}
