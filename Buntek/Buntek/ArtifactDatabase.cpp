#include "ArtifactDatabase.h"
#include "SpriteRenderer.h"
#include "GameManager.h"
#include "BallBehavior.h"
#include <algorithm>
#include "SaveManager.h"

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
    bool flag = false;
    switch (artifact.ID)
    {
    case 000://Increase damage
        if (isPlayerTheCaster) {
            GameManager.playerProfile.bonusDamage = artifact.count * 5;
        }
        else {
            GameManager.enemyProfile.bonusDamage = artifact.count * 5;
        }
        break;
    case 001://Increase max hp
        if (isPlayerTheCaster) {
            GameManager.playerProfile.bonusHp = (float)artifact.count * 10;
        }
        else {
            GameManager.enemyProfile.bonusHp = (float)artifact.count * 10;
        }
        break;
    case 002://Increase paddle speed
        if (isPlayerTheCaster) {
            GameManager.playerProfile.bonusPaddleSpeed = 1 + (float)artifact.count * 0.1f;
        }
        else {
            GameManager.enemyProfile.bonusPaddleSpeed = 1 + (float)artifact.count * 0.1f;
        }
        break;
    case 003://Increase ball speed
        if (isPlayerTheCaster) {
            GameManager.playerProfile.bonusBallSpeed = 1 + (float)artifact.count * 0.1f;
        }
        else {
            GameManager.enemyProfile.bonusBallSpeed = 1 + (float)artifact.count * 0.1f;
        }
        break;
    case 004://Increase ball spawn frequency
        if (isPlayerTheCaster) {
            GameManager.playerProfile.bonusBallSpawnRate = (float)pow(0.9f, artifact.count); // adjust the left float for spawn rate adjustment
            AEClamp(GameManager.playerProfile.bonusBallSpawnRate, 0.1f, 1);
        }
        else {
            GameManager.enemyProfile.bonusBallSpawnRate = (float)pow(0.9f, artifact.count);
            AEClamp(GameManager.enemyProfile.bonusBallSpawnRate, 0.1f, 1);
        }
        break;
    case 030://Heals X times more
        if (isPlayerTheCaster) {
            GameManager.playerProfile.bonusHealing = 1 + (float)artifact.count * 0.2f;
        }
        else {
            GameManager.enemyProfile.bonusHealing = 1 + (float)artifact.count * 0.2f;
        }
        break;
    case 120://Increase hp by 10 per battle won, up to a max of X
        GameManager.playerProfile.basemaxhp += 10 * artifact.count;
        break;
    case 140://Restores 20% hp of max hp
        GameManager.playerHp += (GameManager.playerProfile.basemaxhp + GameManager.playerProfile.bonusHp) * 0.2f * GameManager.playerProfile.bonusHealing;
        break;
    case 220://Increases ball bounce gain by X
        tempBallBehavior = ball->GetComponent<BallBehavior>();
        tempBallBehavior->ballPhase += artifact.count;
        break;
    case 221://Increases ball speed by X
        tempBallBehavior = ball->GetComponent<BallBehavior>();
        tempBallBehavior->SetTargetSpeed(tempBallBehavior->GetSpeed() * (1 + artifact.count * 0.1f));
        break;
    case 300://B2: Increase ball speed by X
        if (ball->GetComponent<BallBehavior>()->ballPhase >= 2) {
            tempBallBehavior = ball->GetComponent<BallBehavior>();
            tempBallBehavior->SetTargetSpeed(tempBallBehavior->GetSpeed() * (1 + artifact.count * 0.1f));
        }
        break;
    case 400://B3: Restores X hp
        if (ball->GetComponent<BallBehavior>()->ballPhase >= 3) {
            if (isPlayerTheCaster) {
                GameManager.playerHp += artifact.count * GameManager.playerProfile.bonusHealing;
            }
            else {
                GameManager.enemyHp += artifact.count * GameManager.enemyProfile.bonusHealing;
            }
        }
        break;
    case 401://B3: Deals extra X damage
        if (ball->GetComponent<BallBehavior>()->ballPhase >= 3) {
            tempBallBehavior = ball->GetComponent<BallBehavior>();
            tempBallBehavior->ballDamage += artifact.count * 7;
        }
        break;
    case 420://B4: Spawns X ball in a random direction forward from the middle
        if (ball->GetComponent<BallBehavior>()->ballPhase >= 4) {
            if (GameManager.bh != NULL) {
                GameManager.bh->SpawnBall(isPlayerTheCaster);
            }
        }
        break;
    case 500://B3: Opponent takes X damage
        if (ball->GetComponent<BallBehavior>()->ballPhase >= 3) {
            if (isPlayerTheCaster) {
                GameManager.enemyHp -= 5 * artifact.count;
            }
            else {
                GameManager.playerHp -= 5 * artifact.count;
            }
        }
        break;
    case 520://B4: Spawns X ball in a random direction forward from the middle
        if (ball->GetComponent<BallBehavior>()->ballPhase >= 4) {
            if (GameManager.bh != NULL) {
                GameManager.bh->SpawnBall(isPlayerTheCaster);
            }
        }
        break;
    case 530://B3: If hp is below <20%, unable to take damage for X second,
        if (ball->GetComponent<BallBehavior>()->ballPhase >= 3) {
            if (isPlayerTheCaster) {
                if (GameManager.playerHp < (GameManager.playerProfile.basemaxhp + GameManager.playerProfile.bonusHp) / 5) {
                    for (size_t i = 0; i < GameManager.playerArtifactList.statusEffect.size(); ++i)
                    {
                        if (GameManager.playerArtifactList.statusEffect[i].statusID == 00) {
                            GameManager.playerArtifactList.statusEffect[i].statusTimer += artifact.count;
                            flag = true;
                            break;
                        }
                    }
                    if (!flag) {
                        Status temp;
                        temp.statusID = 00;
                        temp.statusTimer = (float)artifact.count;
                        GameManager.playerArtifactList.statusEffect.push_back(temp);
                    }
                }
            }
            else {
                if (GameManager.enemyHp < (GameManager.enemyProfile.basemaxhp + GameManager.enemyProfile.bonusHp) / 5) {
                    for (size_t i = 0; i < GameManager.enemyArtifactList.statusEffect.size(); ++i)
                    {
                        if (GameManager.enemyArtifactList.statusEffect[i].statusID == 00) {
                            GameManager.enemyArtifactList.statusEffect[i].statusTimer += artifact.count;
                            flag = true;
                            break;
                        }
                    }
                    if (!flag) {
                        Status temp;
                        temp.statusID = 00;
                        temp.statusTimer = (float)artifact.count;
                        GameManager.enemyArtifactList.statusEffect.push_back(temp);
                    }

                }
            }
        }
        break;
    case 540://B2: Negate next damage
        if (ball->GetComponent<BallBehavior>()->ballPhase >= 4) {
            if (isPlayerTheCaster) {
                for (size_t i = 0; i < GameManager.playerArtifactList.statusEffect.size(); ++i)
                {
                    if (GameManager.playerArtifactList.statusEffect[i].statusID == 00) {
                        GameManager.playerArtifactList.statusEffect[i].statusCount = 1;
                        flag = true;
                        break;
                    }
                }
                if (!flag) {
                    Status temp;
                    temp.statusID = 00;
                    temp.statusCount = 1;
                    GameManager.playerArtifactList.statusEffect.push_back(temp);
                }
            }
            else {
                for (size_t i = 0; i < GameManager.enemyArtifactList.statusEffect.size(); ++i)
                {
                    if (GameManager.enemyArtifactList.statusEffect[i].statusID == 00) {
                        GameManager.enemyArtifactList.statusEffect[i].statusCount = 1;
                        flag = true;
                        break;
                    }
                }
                if (!flag) {
                    Status temp;
                    temp.statusID = 00;
                    temp.statusCount = 1;
                    GameManager.enemyArtifactList.statusEffect.push_back(temp);
                }
            }
        }
        break;
    case 541://On death, restores 50 % hp, destroy this artifact
        if (isPlayerTheCaster) {
            if (artifact.count >= 1 && GameManager.playerHp <= 0) {
                GameManager.playerHp = (GameManager.playerProfile.basemaxhp + GameManager.playerProfile.bonusHp) / 2;
                for (size_t i = 0; i < GameManager.playerArtifactList.behaviorList_TakeDamage.size(); ++i)
                {
                    if (GameManager.playerArtifactList.behaviorList_TakeDamage[i].ID == 541) {
                        GameManager.playerArtifactList.behaviorList_TakeDamage[i].count--;
                        SaveManager.RemoveFromArtifactList(541);
                    }
                }

            }
        }
        else {
            if (artifact.count >= 1 && GameManager.enemyHp <= 0) {
                GameManager.enemyHp = (GameManager.enemyProfile.basemaxhp + GameManager.enemyProfile.bonusHp) / 2;
                for (size_t i = 0; i < GameManager.enemyArtifactList.behaviorList_TakeDamage.size(); ++i)
                {
                    if (GameManager.enemyArtifactList.behaviorList_TakeDamage[i].ID == 541) {
                        GameManager.enemyArtifactList.behaviorList_TakeDamage[i].count--;
                        SaveManager.RemoveFromArtifactList(541);
                    }
                }
            }
        }
        break;
    case 630://B2: Balls colliding with hostile balls will freeze it for X second
        if (ball->GetComponent<BallBehavior>()->ballPhase >= 2) {
            tempBallBehavior = ball->GetComponent<BallBehavior>();
            if (tempBallBehavior->savedCol != NULL) {
                tempBallBehavior = tempBallBehavior->savedCol->Owner()->GetComponent<BallBehavior>();  //get the other ball
            }
            for (size_t i = 0; i < tempBallBehavior->statusEffect.size(); ++i)
            {
                if (tempBallBehavior->statusEffect[i].statusID == 01) {
                    tempBallBehavior->statusEffect[i].statusTimer += artifact.count;;
                    flag = true;
                    break;
                }
            }
            if (!flag) {
                Status temp;
                temp.statusID = 01;
                temp.statusTimer = (float)artifact.count*0.25f; //0.25 second freeze
                tempBallBehavior->statusEffect.push_back(temp);
            }
        }
        break;
    case 631://B2: Colliding with an hostile ball have a chance to reflect that ball
        if (ball->GetComponent<BallBehavior>()->ballPhase >= 2) {
            tempBallBehavior = ball->GetComponent<BallBehavior>();
            flag = tempBallBehavior->playerPossess;
            if (tempBallBehavior->savedCol != NULL) {
                tempBallBehavior = tempBallBehavior->savedCol->Owner()->GetComponent<BallBehavior>();  //get the other ball
                if (tempBallBehavior->playerPossess != flag) {
                    tempBallBehavior->velocity = -tempBallBehavior->velocity;
                    tempBallBehavior->playerPossess = !tempBallBehavior->playerPossess;
                    if (tempBallBehavior->playerPossess) {
                        tempBallBehavior->sr->SetColor(1, 0, 0);
                    }
                    else {
                        tempBallBehavior->sr->SetColor(0, 0, 1);
                    }
                }
            }
        }
        break;
    case 640://B5: Destroys hostile ball
        if (ball->GetComponent<BallBehavior>()->ballPhase >= 5) {
            tempBallBehavior = ball->GetComponent<BallBehavior>();
            if (tempBallBehavior != NULL && !tempBallBehavior->savedCol->Owner()->remove) {
                tempBallBehavior = tempBallBehavior->savedCol->Owner()->GetComponent<BallBehavior>();
                // MUST RemoveFromList before deleting anything with a collider
                CollisionManager2D.RemoveFromList(tempBallBehavior->Owner()->GetComponent<CircleCollider>());
                tempBallBehavior->Owner()->Delete();
                return;
            }
        }
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
    case 0:
        return "Duna";
    case 1:
        return "Orange Juice";
    case 2:
        return "Onion Candy";
    case 3:
        return "Hilo";
    case 4:
        return "Broken Clock";
    case 30:
        return "Leech Medic";
    case 120:
        return "Cool Sock";
    case 140:
        return "Chipped Dagger";
    case 220:
        return "Mocha Latte";
    case 221:
        return "Batter Up";
    case 300:
        return "Galaxial Gourd";
    case 400:
        return "Plastic Fangs";
    case 401:
        return "Bony Caltrops";
    case 420:
        return "Molecular Assembler";
    case 500:
        return "Chicken Soup";
    case 520:
        return "Photonic Banana";
    case 530:
        return "Titanium Fan";
    case 540:
        return "Antimatter Dice";
    case 541:
        return "Nebulous Needle";
    case 630:
        return "Mini Black Hole";
    case 631:
        return "Starry Trampoline";
    case 640:
        return "UwU Glu";
    default:
        return "Invalid ID";
    }
}

RarityTypes _artifactdatabase::GetRarity(unsigned long id)
{
    unsigned long temp = id % 100;
    temp /= 10;

    switch (temp)
    {
    case 2:
        return RarityTypes::Uncommon;
    case 3:
        return RarityTypes::Rare;
    case 4:
        return RarityTypes::Unique;
    default:
        return RarityTypes::Common;
    }
}

string _artifactdatabase::GetDescription(unsigned long id)
{
    switch (id)
    {
    case 0:
        return "Increases damage by 5";
    case 1:
        return "Increases max hp by 10";
    case 2:
        return "Increases paddle speed by 10%";
    case 3:
        return "Increases ball speed by 10%";
    case 4:
        return "Increases ball spawn frequency by 10%";
    case 30:
        return "Increases healing received by 20%";
    case 120:
        return "On battle won: Increases max hp by 10";
    case 140:
        return "On battle won: Restores 20% of max hp";
    case 220:
        return "On wall bounce: Ball phase +1";
    case 221:
        return "On wall bounce: Increases ball speed by 10%";
    case 300:
        return "After 2 reflects, when reflected by your paddle, increase ball speed";
    case 400:
        return "After 3 reflects, when dealing damage, restores 1 hp";
    case 401:
        return "After 3 reflects, when dealing damage, deals 7 extra damage";
    case 420:
        return "After 4 reflects, when dealing damage, spawns a ball in a random direction forward from the middle";
    case 500:
        return "After 3 reflects, when taking damage, opponent takes 5 damage";
    case 520:
        return "After 4 reflects, when taking damage, spawns a ball in a random direction forward from the middle";
    case 530:
        return "After 3 bounces, when taking damage, if hp is below 20%, unable to take damage for a while";
    case 540:
        return "After 4 reflects, when taking damage, negate next damage taken";
    case 541:
        return "On death, restores 50% hp, destroy this artifact";
    case 630:
        return "After 2 reflects, when colliding with hostile balls, freeze the collided ball for 0.25 seconds";
    case 631:
        return "After 2 reflects, when colliding with hostile balls, occasionally reflect collided ball";
    case 640:
        return "After 5 reflects, when colliding with hostile balls, destroy the collided ball";
    default:
        return "Invalid ID";
    }
}

string _artifactdatabase::GetSpriteName(unsigned long id)
{
    string spriteName = "Artifacts/" + GetName(id) + ".png";
    spriteName.erase(remove(spriteName.begin(), spriteName.end(), ' '), spriteName.end());
    return spriteName;
}

void _artifactdatabase::ApplyArtifactBehavior(vector<Artifact> artifactList, bool isPlayerTheCaster, GameObject* ball)
{
    for (size_t i = 0; i < artifactList.size(); ++i)
    {
        ExecuteBehavior(artifactList[i], isPlayerTheCaster, ball);
    }
}

unsigned long _artifactdatabase::DrawArtifact(void)
{
    int RNG = RandIntMinMax(0, 100);

    if (RNG < commonRate)
    {
        RNG = RandIntMinMax(0, (int)common.size() - 1);
        return common[RNG];
    }
    else if (RNG < uncommonRate)
    {
        RNG = RandIntMinMax(0, (int)uncommon.size() - 1);
        return uncommon[RNG];
    }
    else
    {
        RNG = RandIntMinMax(0, (int)rare.size() - 1);
        return rare[RNG];
    }
}

unsigned long _artifactdatabase::DrawLegendary(void)
{
    int RNG = RandIntMinMax(0, (int)legendary.size() - 1);
    return legendary[RNG];
}
