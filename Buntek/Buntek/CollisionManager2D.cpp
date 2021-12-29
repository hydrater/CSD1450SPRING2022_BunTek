#include "CollisionManager2D.h"

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

void _CollisionManager2D::AddToList(Collider2D* collider)
{
    colliderList.push_back(collider);
}

void _CollisionManager2D::CollideAll(void)
{
    for (int i = 0; i < colliderList.size(); ++i)
    {

        for (int j = 1; j < colliderList.size(); ++j)
        {
            if (typeid(colliderList[i]) == typeid(CircleCollider)) {
                ((CircleCollider*)colliderList[i])->Collide(colliderList[j]);
            }
            else if (typeid(colliderList[i]) == typeid(BoxCollider)) {
                ((BoxCollider*)colliderList[i])->Collide(colliderList[j]);
            }

            
        }
    }

}
