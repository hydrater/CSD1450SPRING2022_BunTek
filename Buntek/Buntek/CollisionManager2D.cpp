#include "CollisionManager2D.h"
#include "System.h"

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
