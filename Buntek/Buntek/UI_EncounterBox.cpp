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

void UI_EncounterBox::CreateEncounter(Vector2 position, short sortingLayer, string flag)
{
    GameObject* encounter = this->Owner();
    encounter->transform->SetPosition(position);

    // Background
    SpriteRenderer* tempBckgdRenderer = 0;
    tempBckgdRenderer = encounter->AddComponent<SpriteRenderer>();
    tempBckgdRenderer->Size(1600, 900);
    tempBckgdRenderer->SetTexture("UI/Texture.png");
    tempBckgdRenderer->SetLayer(sortingLayer - 2);


    // Description 
    SpriteRenderer* tempDescRenderer = 0;
    GameObject* tempDescription = devTools.CreateSpriteGameObject("EncounterBox.png", tempBckgdRenderer->GetHalfWidth() / 8 * 10, tempBckgdRenderer->GetHalfHeight(), 
        1, Vector2(0.f, 0.f), (short)(sortingLayer - 1));
    tempDescRenderer = tempDescription->GetComponent<SpriteRenderer>();

    // Description
    TextRenderer* tempDescTxtRenderer = 0;
    tempDescTxtRenderer = tempDescription->AddComponent<TextRenderer>();
    tempDescTxtRenderer->SetFont("Gabriola.ttf");
    tempDescTxtRenderer->SetTextColor(0, 1, 1);
    tempDescTxtRenderer->SetLayer(sortingLayer);
    tempDescTxtRenderer->SetXAlignment(TextRenderer::xAlignmentTypes::Left);
    tempDescTxtRenderer->SetYAlignment(TextRenderer::yAlignmentTypes::Top);
    tempDescription->transform->SetPosition(Vector2(position.x + tempBckgdRenderer->GetHalfWidth()/8*7.5f - tempDescRenderer->GetHalfWidth(),
        position.y + tempBckgdRenderer->GetHalfHeight()/4.5f*3.5f - tempDescRenderer->GetHalfHeight()));
    encounter->AddChild(tempDescription);

    // Header
    GameObject* tempHeader = devTools.CreateSpriteGameObject("UI/Texture.png", tempBckgdRenderer->GetHalfWidth(), tempBckgdRenderer->GetHalfHeight() / 5,
        1, Vector2(0.f, 0.f), (short)(sortingLayer - 1), 0.8f);
    SpriteRenderer* tempHeaderRenderer = 0;
    tempHeaderRenderer = tempHeader->GetComponent<SpriteRenderer>();
    tempHeaderRenderer->SetColor(0, 0, 0.1f);

    // HeaderText
    TextRenderer* tempHeaderTxtRenderer = 0;
    tempHeaderTxtRenderer = tempHeader->AddComponent<TextRenderer>();
    tempHeaderTxtRenderer->SetFont("Gabriola.ttf");
    tempHeaderTxtRenderer->SetTextColor(0, 1, 1);
    tempHeaderTxtRenderer->SetLayer(sortingLayer);
    tempHeaderTxtRenderer->SetYAlignment(TextRenderer::yAlignmentTypes::Mid);
    tempHeaderTxtRenderer->SetXBuffer(50);
    tempHeader->transform->SetPosition(Vector2(position.x - tempHeaderRenderer->GetHalfWidth(), position.y + tempBckgdRenderer->GetHalfHeight() - tempHeaderRenderer->GetHalfHeight()));
    encounter->AddChild(tempHeader);

    // Display
    GameObject* tempDisplay = devTools.CreateSpriteGameObject("Steven.jpg", tempBckgdRenderer->GetHalfWidth() * 2 / 16 * 4, tempBckgdRenderer->GetHalfHeight() * 2 / 9 * 4,
        AE_GFX_BM_BLEND, Vector2(0.f, 0.f), (short)(sortingLayer - 1));
    SpriteRenderer* tempDisplayRenderer = 0;
    tempDisplayRenderer = tempDisplay->GetComponent<SpriteRenderer>();
    tempDisplay->transform->SetPosition(Vector2(position.x - tempBckgdRenderer->GetHalfWidth() /8*7 + tempDisplayRenderer->GetHalfWidth() , position.y));
    encounter->AddChild(tempDisplay);

    // Buttons (Max 3)
    vector<Button*> buttonList;
    for (int i = 0; i < 3; ++i) {
        GameObject* tempButtonObj = devTools.CreateSpriteGameObject("UI/Button.png", tempDescRenderer->GetHalfWidth() * 2, tempDescRenderer->GetHalfHeight() / 3,
            2, Vector2(0.f, 0.f),(short)(sortingLayer - 1));
        SpriteRenderer* tempButtonRenderer = 0;
        tempButtonRenderer = tempButtonObj->GetComponent<SpriteRenderer>();

        TextRenderer* tempButtonTxtRenderer = 0;
        tempButtonTxtRenderer = tempButtonObj->AddComponent<TextRenderer>();
        tempButtonTxtRenderer->SetFont("Gabriola.ttf");
        tempButtonTxtRenderer->SetTextColor(1, 1, 0);
        tempButtonTxtRenderer->SetText("SCREM");
        tempButtonTxtRenderer->SetScale(0.75f);
        tempButtonTxtRenderer->SetLayer(sortingLayer);
        tempButtonTxtRenderer->SetXAlignment(TextRenderer::xAlignmentTypes::Mid);
        tempButtonTxtRenderer->SetYAlignment(TextRenderer::yAlignmentTypes::Mid);

        tempButtonObj->transform->SetPosition(Vector2(tempDescription->transform->worldposition.x ,
            position.y - tempBckgdRenderer->GetHalfHeight() + (i + 0.8f) * tempBckgdRenderer->GetHalfHeight() / 5 + tempBckgdRenderer->GetHalfHeight()/ 9));

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
    MapData.DisplayCurrentRoutes(MapData.playerTravelDistance);
}