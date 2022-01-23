#pragma once
#include <string>
using namespace std;

#define DialogueDatabase _dialogueDatabase::Instance()

class _dialogueDatabase
{
public:
	_dialogueDatabase();
	~_dialogueDatabase();
	static _dialogueDatabase& Instance(void);
	static void SpawnEncounterObject(unsigned long id);
	static string GetName(unsigned long id);
	static string GetDescription(unsigned long id);

private:
	static _dialogueDatabase* instance;
};
