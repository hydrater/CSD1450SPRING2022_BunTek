#include "EncounterBox.h"
#include "Renderer.h"
#include "System.h"
#include <fstream>
#include <sstream>

EncounterBox::EncounterBox(void)
{
}

EncounterBox::~EncounterBox(void)
{
}

void EncounterBox::AssignObjReferences(SpriteRenderer* _header, SpriteRenderer* _display, SpriteRenderer* _background, TextRenderer* _headerText, TextRenderer* _descriptionText, vector<Button*> _buttonList)
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
    for (int i = 0; i < buttonList.size(); ++i)
        buttonList[i]->Owner()->Deactivate();
}

void EncounterBox::StartEncounterEvent(string flag)
{
    buttonNo = 0;
    header->Owner()->Activate();
    display->Owner()->Activate();
    background->Owner()->Activate();
    headerText->Owner()->Activate();
    descriptionText->Owner()->Activate();
    for (int i = 0; i < buttonList.size(); ++i)
        buttonList[i]->Owner()->Activate();
    LoadFromFile(flag);
    WriteToEncounterEvent();
}

void EncounterBox::CloseEncounterEvent(void)
{
    header->Owner()->Deactivate();
    display->Owner()->Deactivate();
    background->Owner()->Deactivate();
    headerText->Owner()->Deactivate();
    descriptionText->Owner()->Deactivate();
    for (int i = 0; i < buttonList.size(); ++i)
        buttonList[i]->Owner()->Deactivate();
}

void EncounterBox::LoadFromFile(string flag)
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

void EncounterBox::WriteToEncounterEvent(void)
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
            Renderer.WrapAround(descriptionText);
        }
    }

    // Deactivate non-used buttons
    for (; buttonNo < buttonList.size(); ++buttonNo)
        buttonList[buttonNo]->Owner()->Deactivate();
}
