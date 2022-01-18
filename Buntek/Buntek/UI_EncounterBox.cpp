#include "MapGenerator.h"
#include "UI_EncounterBox.h"
#include "System.h"
#include <fstream>
#include <sstream>

void RemoveEncounter(Button* button);

UI_EncounterBox::UI_EncounterBox(void)
{
}

UI_EncounterBox::~UI_EncounterBox(void)
{
}

void UI_EncounterBox::CreateEncounter(Vector2 position, int sortingLayer, string flag)
{
    GameObject* encounter = this->Owner();
    encounter->transform->SetPosition(position);

    // Background
    GameObject* tempBackground = new GameObject();
    SpriteRenderer* tempBckgdRenderer = 0;
    tempBckgdRenderer = tempBackground->AddComponent<SpriteRenderer>();
    tempBckgdRenderer->Size(1652, 734);
    tempBckgdRenderer->SetTexture("UI/Texture.png");
    tempBckgdRenderer->SetLayer(sortingLayer - 2);
    encounter->AddChild(tempBackground);

    // Description
    GameObject* tempDescription = new GameObject();
    SpriteRenderer* tempDescRenderer = 0;
    tempDescRenderer = tempDescription->AddComponent<SpriteRenderer>();
    tempDescRenderer->Size(1000, tempBckgdRenderer->GetHalfHeight() / 1.5f);
    tempDescRenderer->SetTexture("UI_EncounterBox.png");
    tempDescRenderer->SetLayer(sortingLayer - 1);

    // Header
    GameObject* tempHeader = new GameObject();
    SpriteRenderer* tempHeaderRenderer = 0;
    tempHeaderRenderer = tempHeader->AddComponent<SpriteRenderer>();
    tempHeaderRenderer->Size(800, 100);
    tempHeaderRenderer->SetTexture("WhiteTexture.png");
    tempHeaderRenderer->SetColor(0, 0, 0.1f);
    tempHeaderRenderer->SetTransparency(0.8f);
    tempHeaderRenderer->SetLayer(sortingLayer - 1);

    // HeaderText
    TextRenderer* tempHeaderTxtRenderer = 0;
    tempHeaderTxtRenderer = tempHeader->AddComponent<TextRenderer>();
    tempHeaderTxtRenderer->SetFont("Gabriola.ttf");
    tempHeaderTxtRenderer->SetTextColor(0, 1, 1);
    tempHeaderTxtRenderer->SetLayer(sortingLayer);
    tempHeaderTxtRenderer->SetYAlignment(TextRenderer::yAlignmentTypes::Mid);
    tempHeaderTxtRenderer->SetXBuffer(50);
    tempHeader->transform->SetPosition(Vector2(position.x - tempBckgdRenderer->GetHalfWidth() + tempHeaderRenderer->GetHalfWidth(), position.y + tempBckgdRenderer->GetHalfHeight() - 20));
    encounter->AddChild(tempHeader);

    // Description
    TextRenderer* tempDescTxtRenderer = 0;
    tempDescTxtRenderer = tempDescription->AddComponent<TextRenderer>();
    tempDescTxtRenderer->SetFont("Gabriola.ttf");
    tempDescTxtRenderer->SetTextColor(0, 1, 1);
    tempDescTxtRenderer->SetLayer(sortingLayer);
    tempDescTxtRenderer->SetXAlignment(TextRenderer::xAlignmentTypes::Left);
    tempDescTxtRenderer->SetYAlignment(TextRenderer::yAlignmentTypes::Top);
    tempDescription->transform->SetPosition(Vector2(position.x + tempBckgdRenderer->GetHalfWidth() - tempDescRenderer->GetHalfWidth() - 20,
        position.y + tempBckgdRenderer->GetHalfHeight() - tempDescRenderer->GetHalfHeight() - 100));
    encounter->AddChild(tempDescription);

    // Display
    GameObject* tempDisplay = new GameObject();
    SpriteRenderer* tempDisplayRenderer = 0;
    tempDisplayRenderer = tempDisplay->AddComponent<SpriteRenderer>();
    tempDisplayRenderer->Size(450, 450);
    tempDisplayRenderer->SetTexture("Steven.jpg");
    tempDisplayRenderer->SetLayer(sortingLayer - 1);
    tempDisplay->transform->SetPosition(Vector2(position.x - tempBckgdRenderer->GetHalfWidth() + tempDisplayRenderer->GetHalfWidth() + 100, position.y + 20));
    encounter->AddChild(tempDisplay);

    // Buttons (Max 3)
    vector<Button*> buttonList;
    for (int i = 0; i < 3; ++i) {
        GameObject* tempButtonObj = new GameObject();
        SpriteRenderer* tempButtonRenderer = 0;
        tempButtonRenderer = tempButtonObj->AddComponent<SpriteRenderer>();
        tempButtonRenderer->Size(504, 56);
        tempButtonRenderer->SetTexture("UI/Button.png");
        tempButtonRenderer->SetBlendMode(2);
        tempButtonRenderer->SetLayer(sortingLayer - 1);

        TextRenderer* tempButtonTxtRenderer = 0;
        tempButtonTxtRenderer = tempButtonObj->AddComponent<TextRenderer>();
        tempButtonTxtRenderer->SetFont("Gabriola.ttf");
        tempButtonTxtRenderer->SetTextColor(1, 1, 0);
        tempButtonTxtRenderer->SetText("SCREM");
        tempButtonTxtRenderer->SetScale(0.75f);
        tempButtonTxtRenderer->SetLayer(sortingLayer);
        tempButtonTxtRenderer->SetXAlignment(TextRenderer::xAlignmentTypes::Mid);
        tempButtonTxtRenderer->SetYAlignment(TextRenderer::yAlignmentTypes::Mid);

        tempButtonObj->transform->SetPosition(Vector2(position.x + tempBckgdRenderer->GetHalfWidth() - tempButtonRenderer->GetHalfWidth() - 300,
            position.y - tempBckgdRenderer->GetHalfHeight() + (i + 1) * tempBckgdRenderer->GetHalfHeight() / 5 + 40));
        Button* tempButton = tempButtonObj->AddComponent<Button>();
        tempButton->sr = tempButtonRenderer;
        tempButton->tr = tempButtonTxtRenderer;
        tempButton->affectedObject = encounter;
        tempButton->ButtonEffect = &RemoveEncounter;

        encounter->AddChild(tempButtonObj);
        buttonList.push_back(tempButton);
    }

    this->AssignObjReferences(tempHeaderRenderer, tempDisplayRenderer, tempBckgdRenderer, tempHeaderTxtRenderer, tempDescTxtRenderer, buttonList);
    this->StartEncounterEvent(flag);
    this->SetClickable(false);
}

void UI_EncounterBox::AssignObjReferences(SpriteRenderer* _header, SpriteRenderer* _display, SpriteRenderer* _background, TextRenderer* _headerText, TextRenderer* _descriptionText, vector<Button*> _buttonList)
{
    header = _header;
    display = _display;
    background = _background;
    headerText = _headerText;
    descriptionText = _descriptionText;
    buttonList = _buttonList;

    header->Owner()->Deactivate();
    display->Owner()->Deactivate();
    background->Owner()->Deactivate();
    headerText->Owner()->Deactivate();
    descriptionText->Owner()->Deactivate();
    for (int i = 0; i < buttonList.size(); ++i) {
        buttonList[i]->Owner()->Deactivate();
        buttonList[i]->Owner()->GetComponent<Button>()->SetClickable(false);
    }
}

void UI_EncounterBox::StartEncounterEvent(string flag)
{
    buttonNo = 0;
    header->Owner()->Activate();
    display->Owner()->Activate();
    background->Owner()->Activate();
    headerText->Owner()->Activate();
    descriptionText->Owner()->Activate();
    for (int i = 0; i < buttonList.size(); ++i) {
        buttonList[i]->Owner()->Activate();
        buttonList[i]->Owner()->GetComponent<Button>()->SetClickable(true);
    }
    LoadFromFile(flag);
    WriteToEncounterEvent();
}

void UI_EncounterBox::CloseEncounterEvent(void)
{
    header->Owner()->Deactivate();
    display->Owner()->Deactivate();
    background->Owner()->Deactivate();
    headerText->Owner()->Deactivate();
    descriptionText->Owner()->Deactivate();
    for (int i = 0; i < buttonList.size(); ++i)
        buttonList[i]->Owner()->Deactivate();
}

void UI_EncounterBox::LoadFromFile(string flag)
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
                descriptNo = 0;
                return;
            }
            else
                descriptList.push_back(inputList[i]);
        }

        if (inputList[i] == flag)
            canAdd = true;
    }
}

void UI_EncounterBox::WriteToEncounterEvent(void)
{
    for (descriptNo = 0; descriptNo < descriptList.size(); ++descriptNo)
    {
        if (descriptList[descriptNo].rfind("/", 0) == 0)
        {
            if (descriptList[descriptNo].length() < 3)
            {
                cout << "Error: Comamnd has no parameters" << endl;
                return;
            }

            string parameters = descriptList[descriptNo].substr(3, descriptList[descriptNo].length());

            switch (descriptList[descriptNo][1])
            {
            case 'i':
                display->SetTexture(parameters);
                break;
            case 'h':
                headerText->SetText(parameters);
                break;

            case 'b':
                if (buttonNo < buttonList.size())
                    buttonList[buttonNo++]->tr->SetText(parameters);
                break;

            default:
                //cout << "default line " << endl;
                break;
            }
        }
        else
        {
            descriptionText->SetText(descriptList[descriptNo]);
            descriptionText->SetWarpAround(true);
        }
    }

    // Deactivate non-used buttons
    for (; buttonNo < buttonList.size(); ++buttonNo)
        buttonList[buttonNo]->Owner()->Deactivate();
}

void UI_EncounterBox::SetClickable(bool _canClick)
{
    for (int i = 0; i < buttonList.size(); ++i)
        buttonList[i]->Owner()->GetComponent<Button>()->SetClickable(_canClick);
}

void RemoveEncounter(Button* button)
{
    GameObject* tmp = button->affectedObject;
    tmp->GetComponent<UI_EncounterBox>()->CloseEncounterEvent();
    MapData.SetClickable(true);
    MapData.SetHoverable(true);
}