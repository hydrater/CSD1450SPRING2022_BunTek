#include "CollisionManager2D.h"
#include "System.h"
#include "BallBehavior.h"
#include "PaddleBehavior.h"

_CollisionManager2D* _CollisionManager2D::instance = 0;

_CollisionManager2D::_CollisionManager2D()
{
}

_CollisionManager2D::~_CollisionManager2D()
{
}

_CollisionManager2D& _CollisionManager2D::Instance(void)
{
    if (instance != 0)
    {
        return *instance;
    }
    instance = new _CollisionManager2D();
    // Init here

    return *instance;
}

void _CollisionManager2D::AddToList(CircleCollider* collider)
{
    circleColliderList.push_back(collider);
}
void _CollisionManager2D::AddToList(BoxCollider* collider)
{
    boxColliderList.push_back(collider);
}
void _CollisionManager2D::AddToList(LineCollider* collider)
{
    lineColliderList.push_back(collider);
}
void _CollisionManager2D::RemoveFromList(CircleCollider* collider)
{
    for (int i = 0; i < circleColliderList.size(); ++i)
    {
        if (circleColliderList[i] == collider)
        {
            circleColliderList.erase(circleColliderList.begin() + i);
            return;
        }
    }
}
void _CollisionManager2D::RemoveFromList(BoxCollider* collider)
{
    for (int i = 0; i < boxColliderList.size(); ++i)
    {
        if (boxColliderList[i] == collider)
        {
            boxColliderList.erase(boxColliderList.begin() + i);
            return;
        }
    }
}
void _CollisionManager2D::RemoveFromList(LineCollider* collider)
{
    for (int i = 0; i < lineColliderList.size(); ++i)
    {
        if (lineColliderList[i] == collider)
        {
            lineColliderList.erase(lineColliderList.begin() + i);
            return;
        }
    }
}

void _CollisionManager2D::CollideAll(void)
{
    //Circles with everything else
    for (int i = 0; i < circleColliderList.size(); ++i)
    {
        for (int j = i+1; j < circleColliderList.size(); ++j)
        {
            (circleColliderList[i])->Collide(circleColliderList[j]);
        }
        for (int j = 0; j < boxColliderList.size(); ++j)
        {
            bool collide = (circleColliderList[i])->Collide(boxColliderList[j]);
            if (collide && circleColliderList[i]->Owner()->GetComponent<BallBehavior>() && boxColliderList[j]->Owner()->GetComponent<PaddleBehavior>())
            {
                bool isPlayer = !circleColliderList[i]->Owner()->GetComponent<BallBehavior>()->playerPossess;
                circleColliderList[i]->Owner()->GetComponent<BallBehavior>()->
                    BounceBall(isPlayer, boxColliderList[j]->Owner(), boxColliderList[j]->Owner()->transform->worldrotation);
            }
        }
    }

    //Boxes with everything else
    for (int i = 0; i < boxColliderList.size(); ++i)
    {
        for (int j = i + 1; j < boxColliderList.size(); ++j)
        {
            (boxColliderList[i])->Collide(boxColliderList[j]);
        }
        for (int j = 0; j < circleColliderList.size(); ++j)
        {
            (boxColliderList[i])->Collide(circleColliderList[j]);
        }
    }
}
