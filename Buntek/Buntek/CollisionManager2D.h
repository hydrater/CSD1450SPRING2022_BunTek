#pragma once

#include <AEEngine.h>
#include "Transform.h"
#include <vector>
#include "System.h"
#include "Collider2D.h"


#define CollisionManager2D _CollisionManager2D::Instance()
#define DeltaTime AEFrameRateControllerGetFrameTime()

class _CollisionManager2D
{
private:
    static _CollisionManager2D* instance;
    _CollisionManager2D();
    ~_CollisionManager2D();
    vector<Collider2D*> colliderList;
    

public:
    static _CollisionManager2D& Instance(void);
    void AddToList(Collider2D* collider);
    void CollideAll(void);
};
