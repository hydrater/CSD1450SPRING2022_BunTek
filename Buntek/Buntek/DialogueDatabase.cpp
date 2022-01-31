#include "DialogueDatabase.h"

_dialogueDatabase::_dialogueDatabase()
{
}

_dialogueDatabase::~_dialogueDatabase()
{
}

_dialogueDatabase& _dialogueDatabase::Instance(void)
{
    static _dialogueDatabase instance;
    return instance;
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
