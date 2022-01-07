#include "DialogueBox.h"
#include <fstream>

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

    dialogue = string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
    cout << dialogue << endl;
}

