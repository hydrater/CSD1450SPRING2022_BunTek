#pragma once

#include <AEEngine.h>
#include "Transform.h"
#include <vector>
#include "System.h"
#include "Collider2D.h"

#define CollisionManager2D _CollisionManager2D::Instance()

class _CollisionManager2D
{
private:
    static _CollisionManager2D* instance;
    _CollisionManager2D();
    ~_CollisionManager2D();
    vector<CircleCollider*> circleColliderList;
    vector<BoxCollider*> boxColliderList;
    

public:
    static _CollisionManager2D& Instance(void);
    void AddToList(CircleCollider* collider);
    void AddToList(BoxCollider* collider);
    void CollideAll(void);
};
