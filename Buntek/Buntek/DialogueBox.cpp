#include "DialogueBox.h"
#include "System.h"
#include <fstream>
#include <sstream>

DialogueBox::DialogueBox(void)
{
}

DialogueBox::~DialogueBox(void)
{
}

void DialogueBox::Start(void)
{
    transform = this->Owner()->transform;

    if (tr)
        tr->SetScale(fontSize); // Set Scale for text

    if (isMainDialogue && sr && actorBox)
    {
        // Get Offset
        Vector2 offset = Vector2(-sr->GetHalfWidth() + actorBox->sr->GetHalfWidth(), sr->GetHalfHeight() + actorBox->sr->GetHalfHeight());
        actorBox->transform->SetPosition(Vector2(transform->worldposition.x + offset.x, transform->worldposition.y + offset.y));

        // Set default as isOpen
        isOpen = false;
        ToggleDisplay(true);
    }
}

void DialogueBox::Update(void)
{
    if (tr != NULL || sr != NULL)
        tr->ScaleTexture(sr);

    if (AEInputCheckTriggered(AEVK_LBUTTON))
        NextDialogue();

    // Show char by char
    if (isOpen && dialogueNo < dialogueList.size())
    {
        displayTimer -= DeltaTime;

        if (displayTimer < 0 && !doneDisplay)
        {
            if (displayNo < dialogueDisplayTxt.size())
                dialogueTxt.append(dialogueDisplayTxt, displayNo++, 1);
            else
                doneDisplay = true;

            tr->SetText(dialogueTxt);

            displayTimer = displaySpeed * DeltaTime;
        }
        else if (doneDisplay)
            tr->SetText(dialogueDisplayTxt);
    }
}

void DialogueBox::LoadFromFile(string flag)
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

void DialogueBox::WriteToDialogue(void)
{
    if (dialogueNo >= dialogueList.size() || !isOpen)
        return;

    if (!isMainDialogue || !actorBox)
        return;

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
            // cout << "Actor Name: " << parameters << endl;
            name = parameters;
            actorBox->tr->SetText(name);
            doneDisplay = true;
            NextDialogue();
            break;

        default:
            cout << "default line " << endl;
            break;
        }
    }
    else
    {
        // cout << dialogueList[dialogueNo] << endl;
        doneDisplay = false;
        displayNo = 0;
        dialogueTxt = "";
        dialogueDisplayTxt = dialogueList[dialogueNo];
    }
}

void DialogueBox::ToggleDisplay(bool flag)
{
    if (flag && !isOpen)
    {
        // Open Dialogue
        isOpen = true;
        doneDisplay = false;
        dialogueNo = 0; 
        displayTimer = 0;
        WriteToDialogue();
        sr->SetTransparency(1);
        if (tr != NULL || sr != NULL)
            tr->ScaleTexture(sr);
        if (actorBox && (actorBox->tr != NULL || actorBox->sr != NULL)) {
            actorBox->sr->SetTransparency(1);
            actorBox->tr->ScaleTexture(sr);
        }
    }
    else if (!flag && isOpen)
    {
        // Close Dialogue
        doneDisplay = false;
        dialogueNo = 0;
        displayTimer = 0;
        tr->SetText("");
        sr->SetTransparency(0);
        if (actorBox) {
            actorBox->tr->SetText("");
            actorBox->sr->SetTransparency(0);
        }
        isOpen = false;
    }
}

void DialogueBox::NextDialogue(void)
{
    if (isOpen)
    {
        if (doneDisplay && dialogueNo < dialogueList.size()) {
            doneDisplay = false;
            ++dialogueNo;
            WriteToDialogue();
        }
        else if (!doneDisplay)
            doneDisplay = true;
    }
}