#include "ArtifactDatabase.h"
#include "SpriteRenderer.h"

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
    case 00000:
        return "test";
        break;
    default:
        return "Invalid ID";
        break;
    }
}

string _artifactdatabase::GetDescription(int id)
{
    switch (id)
    {
    case 00000:
        return "test description";
        break;
    default:
        return "Invalid ID";
        break;
    }
}

void _artifactdatabase::Behavior_Reflect(int id, GameObject* gameObject)
{
    SpriteRenderer* tempRender = 0;
    switch (id)
    {
    case 00000:
        tempRender = gameObject->GetComponent<SpriteRenderer>();
        tempRender->Size(tempRender->GetHalfWidth() * 2/100*101, tempRender->GetHalfHeight() * 2 / 100 * 101);
        break;
    default:
        break;
    }
}

void _artifactdatabase::Behavior_DealDamage(int id, GameObject* gameObject)
{
    switch (id)
    {
    default:
        break;
    }
}

void _artifactdatabase::Behavior_TakeDamage(int id, GameObject* gameObject)
{
    switch (id)
    {
    default:
        break;
    }
}

