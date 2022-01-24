#include "DialogueDatabase.h"

_dialogueDatabase* _dialogueDatabase::instance = 0;

_dialogueDatabase::_dialogueDatabase()
{
}

_dialogueDatabase::~_dialogueDatabase()
{
}

_dialogueDatabase& _dialogueDatabase::Instance(void)
{
    if (instance != 0)
    {
        return *instance;
    }
    instance = new _dialogueDatabase();
    return *instance;
}

void _dialogueDatabase::SpawnEncounterObject(unsigned long id)
{
}

string _dialogueDatabase::GetName(unsigned long id)
{
	return string();
}

string _dialogueDatabase::GetDescription(unsigned long id)
{
	return string();
}
