#include "ArtifactDatabase.h"
#include "SpriteRenderer.h"
#include "GameManager.h"
#include "BallBehavior.h"

_artifactdatabase::_artifactdatabase()
{

}

_artifactdatabase::~_artifactdatabase()
{

}

void _artifactdatabase::ExecuteBehavior(Artifact artifact, bool isPlayerTheCaster, GameObject* ball)
{
    // if (isPlayerTheCaster) means the player owns this artifact else it's the AI
    BallBehavior* tempBallBehavior;
    switch (artifact.ID)
    {
    case 220:
        tempBallBehavior = ball->GetComponent<BallBehavior>();
        tempBallBehavior->ballPhase += artifact.count;
        break;
    case 221:
        tempBallBehavior = ball->GetComponent<BallBehavior>();
        tempBallBehavior->SetTargetSpeed(tempBallBehavior->GetSpeed() * (1 + artifact.count / 10));
        break;
    default:
        
        break;
    }
}

_artifactdatabase& _artifactdatabase::Instance(void)
{
    static _artifactdatabase instance;
    return instance;
}

string _artifactdatabase::GetName(unsigned long id)
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

string _artifactdatabase::GetDescription(unsigned long id)
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

void _artifactdatabase::ApplyArtifactBehavior(vector<Artifact> artifactList, bool isPlayerTheCaster, GameObject* ball)
{
    for (size_t i = 0; i < artifactList.size(); ++i)
    {
        ExecuteBehavior(artifactList[i], isPlayerTheCaster, ball);
    }
}
