#pragma once
#include <AEEngine.h>
#include <vector>
#include <map>
#include "AssetManager.h"
#include "RenderComponent.h"

#define SaveManager _saveManager::Instance()

class _saveManager
{
private:
    static _saveManager* instance;
    _saveManager();
    ~_saveManager();

public:
    static _saveManager& Instance(void);

};