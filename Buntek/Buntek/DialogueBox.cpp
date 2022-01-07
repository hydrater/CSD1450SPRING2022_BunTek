#include "DialogueBox.h"
#include <fstream>
#include <sstream>

DialogueBox::DialogueBox(void)
{
}

DialogueBox::~DialogueBox(void)
{
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
    if (dialogueNo >= dialogueList.size())
        return;

    if (dialogueList[dialogueNo].rfind("/", 0) == 0)
    {
        switch (dialogueList[dialogueNo][1])
        {
        case 'a':
            cout << "command is called " << endl;
            break;

        default:
            cout << "default line " << endl;
            break;
        }
    }
    else
    {
        cout << dialogueList[dialogueNo] << endl;
    }
    ++dialogueNo;
}
