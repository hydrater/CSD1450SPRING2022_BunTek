#include "ArtifactDatabase.h"

_artifactdatabase* _artifactdatabase::instance = 0;


_artifactdatabase::_artifactdatabase()
{

}

_artifactdatabase::~_artifactdatabase()
{

}

_artifactdatabase& _artifactdatabase::Instance(void)
{
    if (instance != 0)
    {
        return *instance;
    }
    instance = new _artifactdatabase();
    return *instance;
}

string _artifactdatabase::GetName(int id)
{
    switch (id)
    {
    default:
        return "Invalid ID";
        break;
    }
}

string _artifactdatabase::GetDescription(int id)
{
    switch (id)
    {
    default:
        return "Invalid ID";
        break;
    }
}

void _artifactdatabase::Behavior_Reflect(int id)
{
    switch (id)
    {
    default:
        break;
    }
}

void _artifactdatabase::Behavior_DealDamage(int id)
{
    switch (id)
    {
    default:
        break;
    }
}

void _artifactdatabase::Behavior_TakeDamage(int id)
{
    switch (id)
    {
    default:
        break;
    }
}

