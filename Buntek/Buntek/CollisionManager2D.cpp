#include "CollisionManager2D.h"
#include "System.h"
#include "BallBehavior.h"
#include "PaddleBehavior.h"
#include "ArtifactDatabase.h"

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

void _CollisionManager2D::RemoveAll(void)
{
    for (int i = circleColliderList.size() - 1; i >= 0; --i)
        circleColliderList.erase(circleColliderList.begin() + i);
    for (int i = boxColliderList.size() - 1; i >= 0; --i)
        boxColliderList.erase(boxColliderList.begin() + i);
    for (int i = lineColliderList.size() - 1; i >= 0; --i)
        lineColliderList.erase(lineColliderList.begin() + i);
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
            (circleColliderList[i])->Collide(boxColliderList[j]);
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

// Returns own self if no collision
Collider2D* _CollisionManager2D::CheckCollision(Collider2D* collider)
{
    for (BoxCollider* otherCol : boxColliderList)
    {
        if (collider != otherCol)
        {
            if (otherCol->Collide(collider))
            {
                return otherCol;
            }
        }
    }
    for (CircleCollider* otherCol : circleColliderList)
    {
        if (collider != otherCol)
        {
            if (otherCol->Collide(collider))
            {
                return otherCol;
            }
        }
    }
    for (LineCollider* otherCol : lineColliderList)
    {
        if (collider != otherCol)
        {
            if (otherCol->Collide(collider))
            {
                return otherCol;
            }
        }
    }
    return nullptr;
}
