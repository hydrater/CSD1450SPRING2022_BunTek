/*!*****************************************************************************
\file CollisionManager2D.h
\project Beyond Aurorean Skies
\author: Algene Tan Chuan Hong (90%)
\co-authors: Isaiah Lim Ji Rong (2.5%), Steven Koe (2.5%), Bryan Boh Tai Hong (2.5%), Goh Kiat Beng (2.5%)
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Manages 2D Collision
All content © 2022 DigiPen Institute of Technology Singapore. All rights reserved.
*******************************************************************************/
#pragma once

#include <AEEngine.h>
#include <vector>
#include "Collider2D.h"

#define CollisionManager2D _CollisionManager2D::Instance()

class _CollisionManager2D
{
private:
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
    void RemoveAll(void);
    void CollideAll(void);
    Collider2D* CheckCollision(Collider2D* collider);
};
