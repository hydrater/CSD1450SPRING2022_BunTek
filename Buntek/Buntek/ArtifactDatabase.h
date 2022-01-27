#pragma once
#include <vector>
#include <string>
#include "Entity.h"
using namespace std;

#define ArtifactDatabase _artifactdatabase::Instance()

enum class RarityTypes : short
{
    Common = 0,
    Rare = 1,
    Lunary = 2,
    Astral = 3,
    Universal = 4
};

// Yo we can have a constellation based on rarity amounts
// Init a list, one for each behavior type
class Artifact
{
public:
    unsigned long ID = 0, count = 0;
    RarityTypes rarity = RarityTypes::Common;
};

class _artifactdatabase
{
private:
    static _artifactdatabase* instance;
    _artifactdatabase();
    ~_artifactdatabase();

public:
    static _artifactdatabase& Instance(void);
    string GetName(int id);
    string GetDescription (int id);
    // Pass in all parameters that u need into these behavior such as object references
    void Behavior_Reflect(int id, GameObject* gameObject);
    void Behavior_DealDamage(int id, GameObject* gameObject);
    void Behavior_TakeDamage(int id, GameObject* gameObject);
};