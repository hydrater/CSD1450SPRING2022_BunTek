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
    _artifactdatabase();
    ~_artifactdatabase();
    // Overload if necessary
    void ExecuteBehavior(Artifact artifact, bool isPlayerTheCaster);

public:
    static _artifactdatabase& Instance(void);
    string GetName(unsigned long id);
    string GetDescription (unsigned long id);
    void ApplyArtifactBehavior(vector<Artifact> artifactList, bool isPlayerTheCaster);
    // Pass in all parameters that u need into these behavior such as object references
    //void Behavior_Reflect(int id, GameObject* gameObject);
    //void Behavior_DealDamage(int id, GameObject* gameObject);
    //void Behavior_TakeDamage(int id, GameObject* gameObject);
};