#pragma once

#include <AEEngine.h>
#include <vector>
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
    vector<LineCollider*> lineColliderList;
    

public:
    static _CollisionManager2D& Instance(void);
    void AddToList(CircleCollider* collider);
    void AddToList(BoxCollider* collider);
    void AddToList(LineCollider* collider);
    void RemoveFromList(CircleCollider* collider);
    void RemoveFromList(BoxCollider* collider);
    void RemoveFromList(LineCollider* collider);
    void CollideAll(void);
};
