#pragma once
#include <vector>
#include "Vector2.h"
#include "Component.h"
#include <AEEngine.h>
#include "SpriteRenderer.h"

#define devTools _devTools::Instance()


class _devTools
{
private:
    static _devTools* instance;
    _devTools();
    ~_devTools();
public:
    
    static _devTools& Instance(void);

    GameObject* CreateSpriteGameObject(string spriteName, float xSize, float ySize, short blendMode, Vector2 pos);

    GameObject* CreateSpriteGameObject(string spriteName, float xSize, float ySize, short blendMode, Vector2 pos, short layer);
};
