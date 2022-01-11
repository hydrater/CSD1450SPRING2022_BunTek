#pragma once
#include <AEEngine.h>
#include <vector>
#include <map>
#include "AssetManager.h"

#define Renderer _Renderer::Instance()

class _Renderer
{
private:
    static _Renderer* instance;
    _Renderer();
    ~_Renderer();

public:
    static _Renderer& Instance(void);
};
